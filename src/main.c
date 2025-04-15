/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/16 00:16:01 by abonifac         ###   ########.fr       */
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
	cmd->argc = token_lstsize(token);
	int count_args = count_arg_words(token);
	cmd->raw = join_tokens_to_string(new_tokens);
	cmd->argv = malloc(sizeof(char *) *( count_args + 1));
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
	print_cmds(cmd_list);

	free_tokens(new_tokens);
	free_tokens_in_list(head_list->tokens, head_list);

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
		ft_printf("Error initializing environment\n");
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
		// exec_command(&minishell, &first);

		free_tokens(token);
		free(line);
		free(first->name);
		free(first->raw);
		free(first->argv);
		free(first);

		
		// print_tokens(token);
		// t_excmd		*prev;
		// t_excmd		*cmd;
		// t_excmd		*first;
		// t_token		*tmp;
		// t_token		*new_tokens;
		// process_tokens(token, &minishell);
		/*
		// On applique ensuite le word splitting sur chaque token.
		// Ici, word_split_token() reçoit un token et son environnement,
			et retourne une nouvelle chaine de tokens */
		// expand_caller(token, &new_tokens, &minishell);
		
		// final_cmd = join_tokens_to_string(new_tokens);
		// tmp = NULL;
		// t_token_list *head_list = NULL;
		// token_list(new_tokens, &head_list);
		// prev = NULL;
		// cmd = NULL;
		// t_token_list *tmp_list = head_list;
		// while(tmp_list)
		// {

		// 	if (tmp_list != NULL)
		// 	{
		// 		tmp = tmp_list->tokens;
		// 		cmd = set_cmd(cmd, tmp, &minishell, new_tokens);

		// 		// char *cmd_name = get_first_word(tmp);
		// 		//  // cmd doit etre le premier WORD rencontre, a changer
		// 		// cmd = create_cmd(cmd_name, &minishell.env);
		// 		// cmd->argc = token_lstsize(tmp);
		// 		// int count_args = count_arg_words(tmp);
		// 		// cmd->raw = join_tokens_to_string(new_tokens);
		// 		// cmd->argv = malloc(sizeof(char *) *( count_args + 1));
		// 		// cmd->argv[count_args] = NULL;
		// 		build_redirs_and_args(cmd, tmp);
		// 		cmd->prev = prev;
		// 		if (prev != NULL)
		// 			prev->next = cmd;
		// 		else
		// 			first = cmd;
		// 		prev = cmd;
		// 	}
		// 	tmp_list = tmp_list->next;
		// }
		// print_cmds(cmd);
		
	}
	return (0);
}

// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<
