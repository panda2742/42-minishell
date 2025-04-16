/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/16 16:50:41 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <strings.h>



void	free_dom_help(t_token *token, t_token *new_tokens,
			t_token_list *token_list, char *line, char *final_cmd, t_excmd *cmd) // to delete
{
	free_tokens(new_tokens);
	free_tokens_in_list(token_list->tokens, token_list);
	free(final_cmd);
	(void)(cmd);
	free_tokens(token);
	free(line);
	free(cmd->name);
	free(cmd->raw);
	free(cmd->argv);
	free(cmd);
}

void	expand_caller(t_token *token, t_token **new_tokens, t_minishell *minishell)
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
		split_token = word_split_token(tmp, &minishell->env);
		if (split_token)
		{
			// Concatene la chaine de tokens obtenue via le word splitting
			if (!*new_tokens)
			{
				*new_tokens = split_token;
				last_new = *new_tokens;
			}
			else
			{
				while (last_new->next)
					last_new = last_new->next;
				last_new->next = split_token;
			}
		}
		tmp = tmp->next;
	}
}

t_excmd *set_cmd(t_excmd *cmd, t_token *token, t_minishell *minishell, t_token *new_tokens)
{
	char *cmd_name = get_first_word(token);
	cmd = create_cmd(cmd_name, &minishell->env);
	if (!cmd)
		return (NULL);
	cmd->argc = token_lstsize(token);
	int count_args = count_arg_words(token);
	cmd->raw = join_tokens_to_string(new_tokens);
	cmd->argv = ft_memalloc(sizeof(char *) *( count_args + 1));
	if (!cmd->argv)
		return (NULL);
	cmd->argv[count_args] = NULL;
	return (cmd);
}

void build_redirs_and_args(t_excmd *cmd, t_token *token)
{
	int i = 0;
	while (token && (token->type != PIPE))
	{
		if (is_redir(token))
		{
			handle_is_redir_tokens(cmd, token);
		}
		if (token->type == WORD)
		{
			cmd->argv[i] = token->text;
			i++;
		}
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
t_excmd *create_cmd_list(t_token_list *token_list_head, t_minishell *minishell, t_token *all_tokens)
{
	t_excmd		*first;
	t_excmd		*prev;
	t_excmd		*cmd;
	t_token_list	*curr_list;

	first = NULL;
	prev = NULL;
	curr_list = token_list_head;
	while (curr_list)
	{
		t_token *cmd_tokens = curr_list->tokens;
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
*/
t_excmd	*process_tokens(t_token *token, t_minishell *minishell)
{
	t_token *new_tokens;
	t_token_list *head_list;
	t_excmd *cmd_list;
	
	new_tokens = NULL;
	expand_caller(token, &new_tokens, minishell);
	head_list = NULL;
	token_list(new_tokens, &head_list);
	cmd_list = create_cmd_list(head_list, minishell, new_tokens);
	// print_cmds(cmd_list);

	free_tokens(new_tokens);
	// free_tokens_in_list(head_list->tokens, head_list);

	return (cmd_list);
	// char *final_cmd;
	// (void)final_cmd;
	// final_cmd = join_tokens_to_string(new_tokens);
	// ft_printf("Final command: %s\n", final_cmd);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_token		*token;

	t_minishell minishell;
	char 		*prompt;

	(void)argc;
	(void)argv;
	if (create_env(env, &minishell.env) == NULL)
	{
		puterr(ft_sprintf(": memory allocation failed"), false);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		set_sig_action();
		prompt = show_prompt(&minishell.env);
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			ft_printf("exit\n");
			free_env(&minishell.env);
			break;
		}
		add_history(line);
		token = ft_input(line);
		if (token == NULL)
		{
			free(line);
			continue;
		}
		if (!lexer_parse(token))
		{
			free_tokens(token);
			free(line);
			continue;
		}
		
		t_excmd *first = NULL;
		
		first = process_tokens(token, &minishell);

		(void)first;
		exec_command(&minishell, &first);
	}
	free_env(&minishell.env);
	return (minishell.last_status);
}

// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<
