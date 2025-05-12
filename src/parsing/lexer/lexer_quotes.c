/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:19:17 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/12 16:26:37 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function is used to parse a quote prefixed fragment.
 * It is called when we encounter a $ followed by a quote in the input string.
 * We are on the $ so we skip it
 * We save the quote type and we read until we find the same quote
 * We create a new fragment with the text between the two quotes
*/
t_err
	parse_quote_prefixed_fragment(t_token *token,
								const char *input, int *i)
{
	char		quote;
	int			start;
	t_fragment	*frag;

	(*i)++;
	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (ERR_LEX);
	if (quote == '\"')
		frag = new_fragment(input + start, *i - start, QUOTE_DOUBLE);
	else
		frag = new_fragment(input + start, *i - start, QUOTE_NONE);
	if (!frag)
		return (ERR_MALLOC);
	append_fragment(token, frag);
	(*i)++;
	return (ERR_NONE);
}

/*
 * In this three functions, we handle the quotes.
 * We skip the first quote, then we look for the closing quote.
 * If we find it, we create a new fragment with the text between the two quotes.
 * If we don't find it, we print an error message and return 0.
 * We also increment the index to skip the closing quote.
 */
int	parse_single_quote(t_token *token, const char *input, int *i)
{
	int			start;
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

int	parse_double_quote(t_token *token, const char *input, int *i)
{
	int			start;
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

int	parse_unquoted(t_token *token, const char *input, int *i)
{
	int			start;
	t_fragment	*frag;

	frag = NULL;
	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& !is_char_redir_or_pipe(input[*i]) && input[*i] != '\''
		&& input[*i] != '\"' && input[*i] != '$')
	{
		(*i)++;
	}
	frag = new_fragment(input + start, *i - start, QUOTE_NONE);
	if (!frag)
		return (ERR_MALLOC);
	append_fragment(token, frag);
	return (ERR_NONE);
}
