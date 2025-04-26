/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:54:00 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/26 18:54:31 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Just some helper funcitons to handle the redirections and pipes
*/

static t_err handle_redir_in(int *i, t_token **l, const char *in)
{
    t_token *tok;

    if (in[*i + 1] == '<')
        tok = ft_create_token(TOKEN_HEREDOC);
    else
        tok = ft_create_token(TOKEN_REDIR_IN);
    if (!tok)
        return (ERR_MALLOC);

    if (in[*i + 1] == '<')
    {
        append_fragment(tok, new_fragment("<<", 2, QUOTE_SINGLE));
        *i += 2;
    }
    else
    {
        append_fragment(tok, new_fragment("<", 1, QUOTE_SINGLE));
        (*i)++;
    }
    append_token(l, tok);
    return (ERR_NONE);
}

static t_err handle_redir_out(int *i, t_token **l, const char *in)
{
    t_token *tok;

    if (in[*i + 1] == '>')
        tok = ft_create_token(TOKEN_APPEND);
    else
        tok = ft_create_token(TOKEN_REDIR_OUT);
    if (!tok)
        return (ERR_MALLOC);

    if (in[*i + 1] == '>')
    {
        append_fragment(tok, new_fragment(">>", 2, QUOTE_SINGLE));
        *i += 2;
    }
    else
    {
        append_fragment(tok, new_fragment(">", 1, QUOTE_SINGLE));
        (*i)++;
    }
    append_token(l, tok);
    return (ERR_NONE);
}

static t_err	handle_pipe(int *i, t_token **token_list)
{
	t_token	*token;

	token = ft_create_token(TOKEN_PIPE);
	if (!token)
		return (ERR_MALLOC);
	append_fragment(token, new_fragment("|", 1, QUOTE_SINGLE));
	append_token(token_list, token);
	(*i)++;
	return (ERR_NONE);
}

/*
 * Handle | and every kind of redir
 */
t_err	handle_redir_pipe(int *i, t_token **token_list, const char *input)
{
	if (input[*i] == '|')
	{
		return (handle_pipe(i, token_list));
	}
	else if (input[*i] == '<')
		return (handle_redir_in(i, token_list, input));
	else if (input[*i] == '>')
		return (handle_redir_out(i, token_list, input));
	return (ERR_NONE);
}
