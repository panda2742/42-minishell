/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:18:54 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/08 15:35:43 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * cmd_name is a copy of the first word of the token list
 * we dup it in create_cmd
*/

static t_excmd	*set_cmd(t_excmd *cmd, t_token *token, t_minishell *minishell)
{
	char	*cmd_name;
	int		count_args;

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

static int	build_redirs_and_args(t_excmd *cmd, t_token *token)
{
	int	i;

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
			cmd->argv[i++] = ft_strdup(token->text);
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

static void	link_prev_cmd(t_excmd **first, t_excmd **prev, t_excmd *cmd)
{
	cmd->prev = *prev;
	if (*prev)
		(*prev)->next = cmd;
	else
		*first = cmd;
	*prev = cmd;
}

static void	cmd_error(t_minishell *mini, t_excmd *first, t_token_list *t_list)
{
	puterr(ft_sprintf(": error: Memory allocation error\n"), false);
	free_env(&mini->env);
	free_tokens_in_list(t_list);
	free_cmds(&first);
	exit(EXIT_FAILURE);
}

/*
 * create_cmd_list creates a list of commands from the token list.
 * a node is a created for each pipe + 1
 * first is the head of the list
 * we call set_cmd to create the command
 * we call build_redirs_and_args to create the redirections and the args
*/
t_excmd	*create_cmd_list(t_token_list *token_list_head, t_minishell *minishell)
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
		cmd = set_cmd(cmd, cmd_tokens, minishell);
		if (!cmd)
			cmd_error(minishell, first, token_list_head);
		link_prev_cmd(&first, &prev, cmd);
		if (!build_redirs_and_args(cmd, cmd_tokens))
			cmd_error(minishell, first, token_list_head);
		curr_list = curr_list->next;
	}
	return (first);
}
