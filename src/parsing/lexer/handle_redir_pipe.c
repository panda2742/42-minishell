/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:54:00 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/22 18:57:57 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir_in(const char *input, int *i, t_token **token_list)
{
	t_token	*token;

	if (input[(*i) + 1] && input[(*i) + 1] == '<')
	{
		token = ft_create_token(TOKEN_HEREDOC);
		if (!token)
			return ;
		append_fragment(token, new_fragment("<<", 2, QUOTE_SINGLE));
		(*i) += 2;
	}
	else
	{
		token = ft_create_token(TOKEN_REDIR_IN);
		if (!token)
			return ;
		append_fragment(token, new_fragment("<", 1, QUOTE_SINGLE));
		(*i)++;
	}
	append_token(token_list, token);
}

static void	handle_redir_out(const char *input, int *i, t_token **token_list)
{
	t_token	*token;

	if (input[(*i) + 1] && input[(*i) + 1] == '>')
	{
		token = ft_create_token(TOKEN_APPEND);
		if (!token)
			return ;
		append_fragment(token, new_fragment(">>", 2, QUOTE_SINGLE));
		(*i) += 2;
	}
	else
	{
		token = ft_create_token(TOKEN_REDIR_OUT);
		if (!token)
			return ;
		append_fragment(token, new_fragment(">", 1, QUOTE_SINGLE));
		(*i)++;
	}
	append_token(token_list, token);
}

static void	*handle_pipe(int *i, t_token **token_list)
{
	t_token	*token;

	token = ft_create_token(TOKEN_PIPE);
	if (!token)
		return (NULL);
	append_fragment(token, new_fragment("|", 1, QUOTE_SINGLE));
	append_token(token_list, token);
	(*i)++;
	return (token);
}

/*
 * Handle | and every kind of redir
 */
void	handle_redir_pipe(int *i, t_token **token_list, const char *input)
{
	if (input[*i] == '|')
	{
		if (handle_pipe(i, token_list) == NULL)
		{
			free(NULL);
		}
	}
	else if (input[*i] == '<')
		handle_redir_in(input, i, token_list);
	else if (input[*i] == '>')
		handle_redir_out(input, i, token_list);
}
