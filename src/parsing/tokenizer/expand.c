/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:01 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/23 16:03:26 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_quote_none(t_fragment *frag, t_minishell *mini,
	t_word_split *new_list, t_token *token)
{
	char	*expanded;

	expanded = expand_fragment(frag->text, frag->quote_type, mini);
	if (!expanded)
	{
	free(new_list->current);
	return (NULL);
	}
	process_unquoted_frag(expanded, &new_list->current, &new_list, token);
	free(expanded);
	return (new_list->current);
}

static char	*handle_other_quotes(t_fragment *frag, t_minishell *mini,
		char *current)
{
	char	*expanded;

	if (frag->quote_type == QUOTE_DOUBLE)
	expanded = expand_fragment(frag->text, frag->quote_type, mini);
	else
	expanded = ft_strdup(frag->text);
	if (!expanded)
	{
	free(current);
	return (NULL);
	}
	current = str_join_free(current, expanded);
	free(expanded);
	return (current);
}

/*
 * Here we go threw the fragments of the token
 * If the fragment is not quoted we check if it needs to be expanded and split
 * If the fragment is quoted we expand it and add it to the current string
 * If strlen(current) > 0 we create a new token with the current string
 * with the function add_new_token
 */

t_token	*word_split_token(t_token *token, t_minishell *mini)
{
	t_word_split	n_list;
	t_fragment		*frag;
 
	n_list.new_head = NULL;
	n_list.new_last = NULL;
	frag = token->fragments;
	n_list.current = ft_strdup("");
	while (frag)
	{
		if (frag->quote_type == QUOTE_NONE)
			n_list.current = handle_quote_none(frag, mini, &n_list, token);
		else
			n_list.current = handle_other_quotes(frag, mini, n_list.current);
		frag = frag->next;
	}
	if (!n_list.current)
		return (NULL);
	n_list.new_head = add_new_token(&n_list.new_head, &n_list.new_last,
			n_list.current, token);
	free(n_list.current);
	return (n_list.new_head);
}
 
void	expand_caller(t_token *token, t_token **new_tokens,
	t_minishell *minishell)
{
	t_token	*last_new;
	t_token	*split_token;
	t_token	*tmp;

	split_token = NULL;
	tmp = token;
	*new_tokens = NULL;
	last_new = NULL;
	while (tmp)
	{
	split_token = word_split_token(tmp, minishell);
	if (split_token)
	{
		if (!*new_tokens)
		{
			*new_tokens = split_token;
			last_new = *new_tokens;
		}
		else {
			while (last_new->next)
				last_new = last_new->next;
			last_new->next = split_token;
		}
	}
	tmp = tmp->next;
	}
}
