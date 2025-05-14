/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 17:07:30 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <strings.h>

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
	t_token			*tok_expand;
	t_excmd			*cmd_list;

	tok_expand = NULL;
	head_list = NULL;
	expand_caller(token, &tok_expand, minishell);
	free_tokens(token);
	token_list(tok_expand, &head_list, minishell);
	free_tokens(tok_expand);
	print_token_list(head_list);
	cmd_list = create_cmd_list(head_list, minishell);
	free_tokens_in_list(head_list);
	if (!cmd_list)
	{
		free_env(&minishell->env);
		free_cmds(&cmd_list);
		exit(EXIT_FAILURE);
	}
	return (cmd_list);
}

t_excmd	*build_and_parse_line(char *line, t_minishell *mini)
{
	t_token	*token;
	t_excmd	*cmd_list;
	t_err	status;

	status = ft_input(line, &token);
	if (*line == '\0')
	{
		free(line);
		mini->last_status = 0;
		free_tokens(token);
		return (NULL);
	}
	free(line);
	if (status == ERR_MALLOC || status == ERR_LEX)
		return (handle_status_err(status, token, mini));
	if (!lexer_parse(token))
	{
		mini->last_status = 2;
		if (token == NULL)
			mini->last_status = 0;
		free_tokens(token);
		return (NULL);
	}
	cmd_list = process_tokens(token, mini);
	return (cmd_list);
}

/*
 * Check if the environment was created successfully
 * If not, print an error message and exit
 * Malloc secured
*/

int	main(int argc, char **argv, char **env)
{
	t_execvars	*vars;
	t_minishell	minishell;
	t_excmd		*first;
	char		*line;

	first = NULL;
	create_env_or_exit_if_env_error(env, &minishell, argc, argv);
	while (1)
	{
		init_sighandler();
		line = show_prompt(&minishell);
		check_sigint(&minishell);
		exit_if_line_null(line, &minishell);
		add_history(line);
		first = build_and_parse_line(line, &minishell);
		if (!first)
			continue ;
		vars = exec_command(&minishell, &first);
		if (vars == NULL)
			minishell.last_status = EXIT_FAILURE;
		else
			minishell.last_status = vars->status;
		free(vars);
	}
	return (minishell.last_status);
}
