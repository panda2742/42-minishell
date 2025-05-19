/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:42:45 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/19 10:45:51 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function set the word after a redir to be REDIR_ARG
 * It also for the quote type to be QUOTE_DOUBLE
 * It is because bash always consider redirs quotes as double quotes
*/
void	update_token_redir(t_token *list)
{
	t_fragment	*tmp;

	tmp = list->next->fragments;
	if (list->type == TOKEN_HEREDOC)
	{
		list->next->type = TOKEN_REDIR_ARG_HEREDOC;
	}
	else
		list->next->type = TOKEN_REDIR_ARG;
	while (tmp)
	{
		if (tmp->quote_type == QUOTE_NONE)
			tmp->quote_type = QUOTE_DOUBLE;
		tmp = tmp->next;
	}
}

static int	check_redir_error(t_token *token)
{
	if (token->next == NULL)
		puterr(ft_strdup(
				": error: syntax error near unexpected token `newline'\n"),
			false);
	if (token->next == NULL)
		return (0);
	if (token->next->type != TOKEN_WORD)
		puterr(ft_strdup(
				": error: syntax error near unexpected token `newline'\n"),
			false);
	if (token->next->type != TOKEN_WORD)
		return (0);
	update_token_redir(token);
	return (1);
}

static int	check_pipe_error(t_token *token)
{
	if (token->next == NULL)
		puterr(ft_strdup(": error: syntax error, end with a | not allowed\n"),
			false);
	if (token->next == NULL)
		return (0);
	if (token->next->type == TOKEN_PIPE)
		puterr(ft_strdup(": error: syntax error, || detected\n"), false);
	if (token->next->type == TOKEN_PIPE)
		return (0);
	return (1);
}

int	lexer_parse(t_token *token)
{
	t_token	*list;

	list = token;
	if (list == NULL)
		return (0);
	if (list->type == TOKEN_PIPE)
		puterr(ft_strdup(": error: syntax error near unexpected token `|'\n"),
			false);
	if (list->type == TOKEN_PIPE)
		return (0);
	while (list != NULL)
	{
		if (list->type == TOKEN_PIPE)
		{
			if (check_pipe_error(list) == 0)
				return (0);
		}
		if (is_redir(list) != 0)
		{
			if (check_redir_error(list) == 0)
				return (0);
		}
		list = list->next;
	}
	return (1);
}
