/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/08 15:28:12 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <strings.h>

/*
 * cmd_name is a copy of the first word of the token list
 * we dup it in create_cmd
*/

t_excmd *set_cmd(t_excmd *cmd, t_token *token, t_minishell *minishell)
{
	char *cmd_name;
	int count_args;

	cmd_name = get_first_word(token);
	cmd = create_cmd(cmd_name, &minishell->env);
	if (!cmd)
		return (NULL);
	cmd->argc = token_lstsize(token);
	count_args = count_arg_words(token);
	cmd->argv = ft_memalloc(sizeof(char *) * (count_args + 1));
	// free(cmd->argv);
	// cmd->argv = NULL;
	if (!cmd->argv)
	{
		free(cmd->name);
		free(cmd);
		return (NULL);
	}
	cmd->argv[count_args] = NULL;
	return (cmd);
}

int build_redirs_and_args(t_excmd *cmd, t_token *token)
{
	int i;

	i = 0;
	while (token && (token->type != TOKEN_PIPE))
	{
		if (is_redir(token))
		{
			if (!handle_is_redir_tokens(cmd, token))
				return (0);
		}
		if (token->type == TOKEN_WORD)
		{
			cmd->argv[i++] =  ft_strdup(token->text);
			// free(cmd->argv[i - 1]);
			// cmd->argv[i -1] = NULL;
			if (!cmd->argv[i - 1])
				return (0);
			free(token->text);
			token->text = NULL;
		}
		token = token->next;
	}
	return (1);
}

void link_prev_cmd(t_excmd **first, t_excmd **prev, t_excmd *cmd)
{
	cmd->prev = *prev;
	if (*prev)
		(*prev)->next = cmd;
	else
		*first = cmd;
	*prev = cmd;
}

t_excmd *create_cmd_list(t_token_list *token_list_head, t_minishell *minishell)
{
	t_excmd *first;
	t_excmd *prev;
	t_excmd *cmd;
	t_token_list *curr_list;
	t_token *cmd_tokens;

	first = NULL;
	prev = NULL;
	curr_list = token_list_head;
	while (curr_list)
	{
		cmd_tokens = curr_list->tokens;
		cmd = set_cmd(cmd, cmd_tokens, minishell);
		if (!cmd)
		{
			puterr(ft_sprintf(": error: Memory allocation error\n"), false);
			free_env(&minishell->env);
			free_tokens_in_list(token_list_head);
			free_cmds(&first);
			exit(EXIT_FAILURE);
		}
		link_prev_cmd(&first, &prev, cmd);
		if (!build_redirs_and_args(cmd, cmd_tokens))
		{
			puterr(ft_sprintf(": error: Memory allocation error\n"), false);
			free_env(&minishell->env);
			free_tokens_in_list(token_list_head);
			free_cmds(&first);
			exit(EXIT_FAILURE);
		}
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

 
t_excmd *process_tokens(t_token *token, t_minishell *minishell)
{
	t_token_list *head_list;
	t_token *tok_expand;
	t_excmd *cmd_list;

	tok_expand = NULL;
	head_list = NULL;
	expand_caller(token, &tok_expand, minishell);
	free_tokens(token);
	token_list(tok_expand, &head_list, minishell);
	free_tokens(tok_expand);
	cmd_list = create_cmd_list(head_list, minishell);
	free_tokens_in_list(head_list);
	return (cmd_list);
}

t_excmd *build_and_parse_line(char *line, t_minishell *mini)
{
	t_token *token;
	t_excmd *cmd_list;
	t_err status;

	status = ft_input(line, &token);
	if (status == ERR_MALLOC)
	{
		puterr(ft_sprintf(": error: Memory allocation error\n"), false);
		free(line);
		free_env(&mini->env);
		exit(EXIT_FAILURE);
	}
	else if (status == ERR_LEX)
	{
		puterr(ft_sprintf(": error: Lexical error\n"), false);
		free(line);
		mini->last_status = 2;
		free_tokens(token);
		return (NULL);
	}
	if (!lexer_parse(token))
	{
		free(line);
		mini->last_status = 2;
		free_tokens(token);
		return (NULL);
	}
	cmd_list = process_tokens(token, mini);
	free(line);
	return (cmd_list);
}

void exit_if_line_null(char *line, t_minishell *minishell)
{
	if (!line)
	{
		free_env(&minishell->env);
		line = NULL;
		printf("exit\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * Check if the environment was created successfully
 * If not, print an error message and exit
 * Malloc secured
*/
void	create_env_or_exit_if_env_error(char **env, t_minishell *minishell,
										int argc, char **argv)
{
	t_env_var **env_var;

	minishell->argc = argc;
	minishell->argv = argv;
	minishell->prompt_theme = -1;
	minishell->last_status = EXIT_SUCCESS;
	env_var = create_env(env, &minishell->env);
	if (env_var == NULL)
	{
		puterr(ft_sprintf(
				   ": error: Environment creation memory allocation failure\n"),
			   false);
		exit (EXIT_FAILURE);
	}
}

void handle_status_error(t_token *token, t_minishell *minishell, t_err status)
{
	if (status == ERR_MALLOC)
	{

		puterr(ft_sprintf(": error: Memory allocation error\n"), false);
		free_tokens(token);
		free_env(&minishell->env);
		exit (EXIT_FAILURE);
	}
	else
	{
			free_tokens(token);
	}
}
int main(int argc, char **argv, char **env)
{
	t_execvars *vars;
	t_minishell minishell;
	t_excmd *head;
	t_excmd *first;
	char *line;

	first = NULL;
	head = NULL;
	create_env_or_exit_if_env_error(env, &minishell, argc, argv);
	while (1)
	{
		set_sig_action();
		line = show_prompt(&minishell); // line secured
		exit_if_line_null(line, &minishell);
		add_history(line);
		first = build_and_parse_line(line, &minishell);
		if (!first)
			continue;
		if (head == NULL)
			head = first;
		
		vars = exec_command(&minishell, &first);
		if (vars == NULL)
			minishell.last_status = EXIT_FAILURE;
		else
			minishell.last_status = vars->status;
		free(vars);
	}
	return (minishell.last_status);
}
