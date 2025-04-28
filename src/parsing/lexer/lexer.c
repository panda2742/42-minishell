/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:59:55 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/28 10:42:32 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * In this three functions, we handle the quotes.
 * We skip the first quote, then we look for the closing quote.
 * If we find it, we create a new fragment with the text between the two quotes.
 * If we don't find it, we print an error message and return 0.
 * We also increment the index to skip the closing quote.
 */
static int parse_single_quote(t_token *token, const char *input, int *i)
{
	int start;
	t_fragment	*frag;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] != '\'')
	{
		ft_printf("Quotes not closed\n");
		return (ERR_LEX);
	}
	frag = new_fragment(input + start, *i - start, QUOTE_SINGLE);
	if (!frag)
		return (ERR_MALLOC);
	append_fragment(token, frag);
	(*i)++;
	return (ERR_NONE);
}

static int parse_double_quote(t_token *token, const char *input, int *i)
{
	int start;
	t_fragment	*frag;
	
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\"')
		(*i)++;
	if (input[*i] != '\"')
	{
		ft_printf("Quotes not closed\n");
		return (ERR_LEX);
	}
	frag = new_fragment(input + start, *i - start, QUOTE_DOUBLE);
	if (!frag)
		return (ERR_MALLOC);
	append_fragment(token, frag);
	(*i)++;
	return (ERR_NONE);
}

static int parse_unquoted(t_token *token, const char *input, int *i)
{
	int start;
	t_fragment	*frag;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_char_redir_or_pipe(input[*i]) && input[*i] != '\'' && input[*i] != '\"')
	{
		(*i)++;
	}
	frag = new_fragment(input + start, *i - start, QUOTE_NONE);
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
static t_err parse_word_token(const char *input, int *i, t_token **curr)
{
	t_token *token;
	t_err status;

	token = ft_create_token(TOKEN_WORD);
	if (token == NULL)
		return (ERR_MALLOC);
	while (input[*i] && !ft_isspace(input[*i]) && !is_char_redir_or_pipe(input[*i]))
	{
		if (input[*i] == '\'')
		{
			status = parse_single_quote(token, input, i);
		}
		else if (input[*i] == '\"')
		{
			status = parse_double_quote(token, input, i);
		}
		else
		{
			status = parse_unquoted(token, input, i);
		}
		if (status != ERR_NONE)
		{
			free(token);
			return (status);
		}
	}
	*curr = token;
	return (ERR_NONE);
}

/*
 * For each elemt of the input string, we skip spaces,
 * we handle redirection/pipe tokens via handle_redir_pipe, or we build
 * a TOKEN_WORD token by accumulating its fragments.
 */
t_err ft_input(const char *input, t_token **output)
{
	t_token *curr_token;
	t_err status;
	int i;

	*output = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break;
		if (is_char_redir_or_pipe(input[i]))
		{
			status = handle_redir_pipe(&i, output, input);
			continue;
		}
		status = parse_word_token(input, &i, &curr_token);
		if (status != ERR_NONE)
			return (status);
		append_token(output, curr_token);
	}
	return (ERR_NONE);
}
