/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/22 19:11:39 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <strings.h>

void	expand_caller(t_token *token, t_token **new_tokens,
			t_minishell *minishell)
{
	t_token	*last_new;
	t_token	*split_token;
	t_token	*tmp;

	split_token = NULL;
	tmp = token;
	*new_tokens = NULL;
	last_new = NULL;
	while (tmp)
	{
		split_token = word_split_token(tmp, minishell);
		if (split_token)
		{
			if (!*new_tokens)
			{
				*new_tokens = split_token;
				last_new = *new_tokens;
			}
			else {
				while (last_new->next)
					last_new = last_new->next;
				last_new->next = split_token;
			}
		}
		tmp = tmp->next;
	}
}

t_excmd	*set_cmd(t_excmd *cmd, t_token *token, t_minishell *minishell,
			t_token *new_tokens)
{
	char	*cmd_name;
	int		count_args;

	cmd_name = get_first_word(token);
	cmd = create_cmd(cmd_name, &minishell->env);
	if (!cmd)
		return (NULL);
	cmd->argc = token_lstsize(token);
	count_args = count_arg_words(token);
	cmd->raw = join_tokens_to_string(new_tokens);
	cmd->argv = ft_memalloc(sizeof(char *) * (count_args + 1));
	if (!cmd->argv)
		return (NULL);
	cmd->argv[count_args] = NULL;
	return (cmd);
}

void	build_redirs_and_args(t_excmd *cmd, t_token *token)
{
	int	i;

	i = 0;
	while (token && (token->type != TOKEN_PIPE))
	{
		if (is_redir(token))
			handle_is_redir_tokens(cmd, token);
		if (token->type == TOKEN_WORD)
			cmd->argv[i++] = token->text;
		token = token->next;
	}
}

void	link_prev_cmd(t_excmd **first, t_excmd **prev, t_excmd *cmd)
{
	cmd->prev = *prev;
	if (*prev)
		(*prev)->next = cmd;
	else
		*first = cmd;
	*prev = cmd;
}

t_excmd	*create_cmd_list(t_token_list *token_list_head, t_minishell *minishell,
			t_token *all_tokens)
{
	t_excmd			*first;
	t_excmd			*prev;
	t_excmd			*cmd;
	t_token_list	*curr_list;
	t_token			*cmd_tokens;

	first = NULL;
	prev = NULL;
	curr_list = token_list_head;
	while (curr_list)
	{
		cmd_tokens = curr_list->tokens;
		cmd = set_cmd(cmd, cmd_tokens, minishell, all_tokens);
		if (!cmd)
		{
			puterr(ft_sprintf(": memory allocation error"), false);
			free_cmds(&first);
			return (NULL);
		}
		build_redirs_and_args(cmd, cmd_tokens);
		link_prev_cmd(&first, &prev, cmd);
		curr_list = curr_list->next;
	}
	return (first);
}

/*
* Process the tokens after the lexer and parser
* 1. Expand the tokens
* 2. Create a new list of tokens fully expanded
* 3. Create a list of commands
* new_tokens is the list of tokens after expansion
*/
t_excmd	*process_tokens(t_token *token, t_minishell *minishell)
{
	t_token_list	*head_list;
	t_token			*new_tokens;
	t_excmd			*cmd_list;

	new_tokens = NULL;
	head_list = NULL;
	expand_caller(token, &new_tokens, minishell);
	free_tokens(token);
	token_list(new_tokens, &head_list);
	cmd_list = create_cmd_list(head_list, minishell, new_tokens);
	free_tokens_in_list(head_list);
	free_tokens(new_tokens);
	return (cmd_list);
}

int	main(int argc, char **argv, char **env)
{
	t_execparams	params;
	t_minishell		minishell;
	t_excmd			*first;
	t_token			*token;
	char			*line;
	char			*prompt;

	first = NULL;
	(void)argc;
	(void)argv;
	if (create_env(env, &minishell.env) == NULL)
	{
		puterr(ft_sprintf(
			": error: Environment creation memory allocation failure\n"
			), false);
		return (EXIT_FAILURE);
	}
	minishell.last_status = EXIT_SUCCESS;
	while (1)
	{
		set_sig_action();
		prompt = show_prompt(&minishell.env);
		if (prompt == NULL || minishell.last_status == -2)
		{
			if (prompt)
				free(prompt);
			free_env(&minishell.env);
			return (EXIT_FAILURE);
		}
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			free_env(&minishell.env);
			printf(B_GREEN "Good bye!\n" RESET);
			// Il faut un meilleur paramètre pour free cmds
			// if (first)
			// 	free_cmds(&first);
			return (EXIT_SUCCESS);
		}
		add_history(line);
		token = ft_input(line);
		if (token == NULL)
		{
			free(line);
			continue ;
		}
		if (!lexer_parse(token))
		{
			free_tokens(token);
			free(line);
			continue ;
		}
		first = process_tokens(token, &minishell);
		
		(void) params;
		// print_cmds(first);
		params = exec_command(&minishell, &first);
		minishell.last_status = params.status;
		printf("prev status: %d\n", params.status);
		free(line);
	}
	free_env(&minishell.env);
	return (minishell.last_status);
}

// ptit test