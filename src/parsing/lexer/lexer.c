/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:59:55 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/13 10:48:36 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function is used to parse a variable fragment.
 * It is called when we encounter a $ in the input string.
 * We strart on the $ so we skip it
 * new_fragment return null if fail
*/
static t_fragment *
	parse_variable_fragment(const char *input, int *i)
{
	int			start;
	t_fragment	*frag;

	start = *i;
	(*i)++;
	if (input[*i] == '?')
		(*i)++;
	else
		while (input[*i] && ft_isalnum(input[*i]))
			(*i)++;
	frag = new_fragment(input + start, *i - start, QUOTE_NONE);
	return (frag);
}

t_err	free_tok_return_st(t_token *token, t_err status)
{
	free_tokens(token);
	return (status);
}

t_err	helper_dollar(const char *input, int *i, t_token *token)
{
	t_fragment	*frag;

	frag = parse_variable_fragment(input, i);
	if (!frag)
		return (ERR_MALLOC);
	append_fragment(token, frag);
	return (ERR_NONE);
}
/*
 * We build a TOKEN_WORD token by accumulating its fragments until we meet a
 * delimiter.
 * A delimiter is a space, a redirection or a pipe.
 */

static t_err	parse_word_token(const char *input, int *i, t_token **out)
{
	t_token	*token;
	t_err	st;

	token = ft_create_token(TOKEN_WORD);
	if (!token)
		return (ERR_MALLOC);
	while (input[*i] && !ft_isspace(input[*i])
		&& !is_char_redir_or_pipe(input[*i]))
	{
		if (input[*i] == '\'')
			st = parse_single_quote(token, input, i);
		else if (input[*i] == '\"')
			st = parse_double_quote(token, input, i);
		else if (input[*i] == '$' && (input[*i + 1] == '\''
				|| input[*i + 1] == '\"'))
			st = parse_quote_prefixed_fragment(token, input, i);
		else if (input[*i] == '$')
			st = helper_dollar(input, i, token);
		else
			st = parse_unquoted(token, input, i);
		if (st != ERR_NONE)
			return (free_tok_return_st(token, st));
	}
	*out = token;
	return (ERR_NONE);
}

/*
 * For each elemt of the input string, we skip spaces,
 * we handle redirection/pipe tokens via handle_redir_pipe, or we build
 * a TOKEN_WORD token by accumulating its fragments.
 */

t_err	ft_input(const char *input, t_token **output)
{
	t_token	*curr_token;
	t_err	status;
	int		i;

	curr_token = NULL;
	*output = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (is_char_redir_or_pipe(input[i]))
		{
			status = handle_redir_pipe(&i, output, input);
			continue ;
		}
		status = parse_word_token(input, &i, &curr_token);
		// status = ERR_MALLOC;
		if (status != ERR_NONE)
			return (status);
		append_token(output, curr_token);
	}
	return (ERR_NONE);
}