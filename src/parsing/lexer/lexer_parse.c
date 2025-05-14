/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:42:45 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/13 15:56:45 by abonifac         ###   ########.fr       */
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

int	ft_printf_error(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	return (0);
}

static int	check_redir_error(t_token *token)
{
	if (token->next == NULL)
		return (
			ft_printf_error
			("Error: syntax error near unexpected token `newline'\n"));
	if (token->next->type != TOKEN_WORD)
		return (
			ft_printf_error
			("Error: syntax error near unexpected token `newline'\n"));
	update_token_redir(token);
	return (1);
}

static int	check_pipe_error(t_token *token)
{
	if (token->next == NULL)
		return (ft_printf_error
			("Error: syntax error end with a | not allowed\n"));
	if (token->next->type == TOKEN_PIPE)
		return (ft_printf_error("Error: syntax error || detected\n"));
	return (1);
}

int	lexer_parse(t_token *token)
{
	t_token	*list;

	list = token;
	if (list == NULL)
		return (0);
	if (list->type == TOKEN_PIPE)
		return (
			ft_printf_error("Error: syntax error near unexpected token `|'\n"));
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
