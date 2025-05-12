/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:42:29 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/12 15:17:36 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Here we check if there is a $ in the fragmentstring
 * We use i and j to find the $ and the end of the variable
 * In handler functions we join everything in the string utils.s1
 * if there is no $ we joins the chars one by one
 * if there is a ? we get the last return value
 * if j > i + 1 it means there is a variable name
 * else it means there is jus a signle $ so we print it 
 */
char	*expand_fragment(const char *input, int quote, t_minishell *mini)
{
	t_utils	u;
	t_err	st;

	ft_memset(&u, 0, sizeof(u));
	u.s1 = ft_strdup("");
	if (!u.s1)
		return (NULL);
	while (input[u.i])
	{
		if (input[u.i] == '$' && quote != QUOTE_SINGLE)
		{
			incr_on_alnum((char *)input, &u.j, u.i + 1);
			if (input[u.j] == '?')
				st = handle_last_rvalue(mini, &u);
			else if (u.j > u.i + 1)
				st = handle_expand_char(&u, mini, (char *)input);
			else
				st = handle_normal_char(&u, (char *)input);
		}
		else
			st = handle_normal_char(&u, (char *)input);
		if (st != ERR_NONE)
			return (free_str_return_null(u.s1));
	}
	return (u.s1);
}

static t_token	*create_new_token_from_word(const char *word,
									t_token *token_head)
{
	t_token	*token;

	token = ft_memalloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_head->type;
	token->index = 0;
	token->next = NULL;
	token->quote_type = set_qtype_fragment(token_head);
	token->fragments = ft_memalloc(sizeof(t_fragment));
	if (!token->fragments)
	{
		free(token);
		return (NULL);
	}
	token->fragments->text = ft_strdup(word);
	if (!token->fragments->text)
	{
		free(token->fragments);
		free(token);
		return (NULL);
	}
	token->fragments->quote_type = set_qtype_fragment(token_head);
	token->fragments->next = NULL;
	return (token);
}

static t_err	helper_create_new_token(char **current, t_w_split **new_list,
					t_token *token, t_token *n_tok)
{
	n_tok = create_new_token_from_word(*current, token);
	if (!n_tok)
		return (ERR_MALLOC);
	update_head_and_last(&(*new_list)->new_h, &(*new_list)->new_t, n_tok);
	free(*current);
	*current = ft_strdup("");
	if (current == NULL)
		return (ERR_MALLOC);
	return (ERR_NONE);
}

/*
 * new_h is the head of the new token list
 * new_t is the last token of the new token list
 * Current is the current string we are building
 * When we find a space we create a new token with the current string
 * and add it to the new token list
 */

t_err	process_unquoted_frag(const char *expanded, char **current,
							t_w_split **new_list, t_token *token)
{
	int			i;
	t_token		*n_tok;

	n_tok = NULL;
	i = 0;
	while (expanded[i])
	{
		if (ft_isspace(expanded[i]))
		{
			if ((*current)[0] != '\0')
			{
				if (helper_create_new_token(current, new_list, token, n_tok)
					!= ERR_NONE)
					return (ERR_MALLOC);
			}
			while (expanded[i] && ft_isspace(expanded[i]))
				i++;
		}
		else
		{
			if (add_char_to_string((char *)expanded, current, &i) != ERR_NONE)
				return (ERR_MALLOC);
		}
	}
	return (ERR_NONE);
}

t_token	*add_new_token(t_token **new_h, t_token **new_t,
						char *current, t_token *token)
{
	t_token	*new_token;

	new_token = create_new_token_from_word(current, token);
	if (!new_token)
		return (NULL);
	if (!*new_h)
		*new_h = new_token;
	else
		(*new_t)->next = new_token;
	*new_t = new_token;
	free(current);
	return (new_token);
}
