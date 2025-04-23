/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:59:55 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/22 18:57:46 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_single_quote(t_token *token, const char *input, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] != '\'')
	{
		ft_printf("Quotes not closed\n");
		return (0);
	}
	append_fragment(token, new_fragment(input + start, *i - start,
			QUOTE_SINGLE));
	(*i)++;
	return (1);
}

static int	parse_double_quote(t_token *token, const char *input, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\"')
		(*i)++;
	if (input[*i] != '\"')
	{
		ft_printf("Quotes not closed\n");
		return (0);
	}
	append_fragment(token, new_fragment(input + start, *i - start,
			QUOTE_DOUBLE));
	(*i)++;
	return (1);
}

static int	parse_unquoted(t_token *token, const char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& !is_char_redir_or_pipe(input[*i]) && input[*i] != '\''
		&& input[*i] != '\"')
	{
		(*i)++;
	}
	append_fragment(token, new_fragment(input + start, *i - start, QUOTE_NONE));
	return (1);
}

/*
* Construit un token TOKEN_WORD en accumulant ses fragments jusqu'a rencontrer un
* delimiteur.
*/
static t_token	*parse_word_token(const char *input, int *i)
{
	t_token	*token;

	token = ft_create_token(TOKEN_WORD);
	if (token == NULL)
		return (NULL);
	while (input[*i] && !ft_isspace(input[*i])
		&& !is_char_redir_or_pipe(input[*i]))
	{
		if (input[*i] == '\'')
		{
			if (parse_single_quote(token, input, i) == 0)
				return (NULL);
		}
		else if (input[*i] == '\"')
		{
			if (parse_double_quote(token, input, i) == 0)
				return (NULL);
		}
		else
		{
			if (parse_unquoted(token, input, i) == 0)
				return (NULL);
		}
	}
	return (token);
}

/*
** Pour chaque element de la chaine d'entree, on saute les espaces,
** on gere les tokens de redirection/pipe via handle_redir_pipe, ou on construit
** un token TOKEN_WORD en accumulant ses fragments.
*/
t_token	*ft_input(const char *input)
{
	t_token	*token_list;
	t_token	*curr_token;
	int		i;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (is_char_redir_or_pipe(input[i]))
		{
			handle_redir_pipe(&i, &token_list, input);
			continue ;
		}
		curr_token = parse_word_token(input, &i);
		if (curr_token == NULL)
			return (NULL);
		append_token(&token_list, curr_token);
	}
	return (token_list);
}
