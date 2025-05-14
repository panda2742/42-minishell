/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:01 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/14 14:27:37 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_err	handle_quote_none(t_fragment *frag, t_minishell *mini,
						t_w_split *new_list, t_token *token)
{
	char	*expanded;
	t_err	status;

	expanded = expand_fragment(frag->text, frag->quote_type, mini);
	if (!expanded)
		return (ERR_MALLOC);
	status = process_unquoted_frag(expanded, &new_list->current,
			&new_list, token);
	free(expanded);
	if (status != ERR_NONE)
	{
		return (status);
	}
	return (ERR_NONE);
}

static t_err	handle_other_quotes(t_fragment *frag, t_w_split *n_list,
			t_minishell *mini, t_token *tok)
{
	char	*expanded;
	char	*tmp;

	n_list->has_quotes = true;
	if (frag->quote_type == QUOTE_DOUBLE
		&& tok->type != TOKEN_REDIR_ARG_HEREDOC)
		expanded = expand_fragment(frag->text, frag->quote_type, mini);
	else
		expanded = ft_strdup(frag->text);
	if (!expanded)
		return (ERR_MALLOC);
	tmp = str_join_free(n_list->current, expanded);
	free(expanded);
	if (!tmp)
		return (ERR_MALLOC);
	n_list->current = tmp;
	return (ERR_NONE);
}

static t_err	apply_fragments(t_w_split *n, t_fragment *frag,
	t_minishell *mini, t_token *tok)
{
	t_err	st;

	while (frag)
	{
		if (frag->quote_type == QUOTE_NONE
			&& tok->type != TOKEN_REDIR_ARG_HEREDOC)
			st = handle_quote_none(frag, mini, n, tok);
		else
		{
			n->has_quotes = true;
			st = handle_other_quotes(frag, n, mini, tok);
		}
		if (st != ERR_NONE)
			return (st);
		frag = frag->next;
	}
	return (ERR_NONE);
}
/*
 * Here we go threw the fragments of the token
 * If the fragment is not quoted we check if it needs to be expanded and split
 * If the fragment is quoted we expand it and add it to the current string
 * If strlen(current) > 0 we create a new token with the current string
 * with the function add_new_token
 */

static t_err	word_split_token(t_token *token, t_minishell *mini,
					t_token **out_list)
{
	t_w_split	n_list;
	t_fragment	*frag;
	t_token		*added;
	t_err		status;

	frag = token->fragments;
	set_n_list_and_frag(&n_list);
	if (!n_list.current)
		return (ERR_MALLOC);
	status = apply_fragments(&n_list, frag, mini, token);
	if (status != ERR_NONE)
		return (free_n_list(&n_list));
	if (n_list.has_quotes == false && n_list.current[0] == '\0')
		return (empty_var(&n_list, out_list));
	added = add_new_token(&n_list.new_h, &n_list.new_t, n_list.current, token);
	if (!added)
		return (free_n_list(&n_list));
	*out_list = n_list.new_h;
	return (ERR_NONE);
}

void	expand_caller(t_token *token, t_token **new_tokens, t_minishell *mini)
{
	t_token	*last_new;
	t_token	*split_token;
	t_token	*tmp;
	t_err	st;

	split_token = NULL;
	*new_tokens = NULL;
	last_new = NULL;
	tmp = token;
	while (tmp)
	{
		st = word_split_token(tmp, mini, &split_token);
		if (st == ERR_MALLOC)
			split_error(token, mini, st, new_tokens);
		if (!*new_tokens)
			*new_tokens = split_token;
		else
			last_new->next = split_token;
		if (split_token)
			last_new = get_tail(split_token);
		tmp = tmp->next;
	}
}
