/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:01 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/29 18:07:42 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sortie propre
t_err handle_quote_none(t_fragment *frag, t_minishell *mini,
						t_w_split *new_list, t_token *token)
{
	char *expanded;
	t_err status;

	expanded = expand_fragment(frag->text, frag->quote_type, mini);
	// free(expanded);
	// expanded = NULL;
	if (!expanded)
		return (ERR_MALLOC);
	status = process_unquoted_frag(expanded, &new_list->current, &new_list, token);
	free(expanded);
	if (status != ERR_NONE)
	{
		// free(new_list->current); // j ai test de l enlever a voir?
		return (status);
	}
	return (ERR_NONE);
}

t_err handle_other_quotes(t_fragment *frag, t_w_split *n_list, t_minishell *mini)
{
	char *expanded;
	char *tmp;

	if (frag->quote_type == QUOTE_DOUBLE)
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

/*
 * Here we go threw the fragments of the token
 * If the fragment is not quoted we check if it needs to be expanded and split
 * If the fragment is quoted we expand it and add it to the current string
 * If strlen(current) > 0 we create a new token with the current string
 * with the function add_new_token
 */

t_err word_split_token(t_token *token, t_minishell *mini, t_token **out_list)
{
	t_w_split n_list;
	t_fragment *frag;
	t_token *added;
	t_err status;

	n_list.new_h = NULL;
	n_list.new_t = NULL;
	frag = token->fragments;
	n_list.has_quotes = false;
	n_list.current = ft_strdup("");
	if (!n_list.current)
		return (ERR_MALLOC);

	while (frag)
	{
		if (frag->quote_type == QUOTE_NONE)
			status = handle_quote_none(frag, mini, &n_list, token);
		else
		{
			n_list.has_quotes = true;
			status = handle_other_quotes(frag, &n_list, mini);
		}

		if (status != ERR_NONE)
		{
			free(n_list.current);
			free_tokens(n_list.new_h);
			return (ERR_MALLOC);
		}
		frag = frag->next;
	}
	
	if (n_list.has_quotes == false && n_list.current[0] == '\0')
	{
		free(n_list.current);
		*out_list = n_list.new_h;
		return (ERR_NONE);
	}
	added = add_new_token(&n_list.new_h, &n_list.new_t, n_list.current, token);
	free(n_list.current);
	if (!added)
	{
		free_tokens(n_list.new_h);
		return (ERR_MALLOC);
	}
	*out_list = n_list.new_h;
	return (ERR_NONE);
}

static t_token *get_tail(t_token *tok)
{
	while (tok->next)
		tok = tok->next;
	return (tok);
}

void expand_caller(t_token *token, t_token **new_tokens, t_minishell *mini)
{
	t_token *last_new;
	t_token *split_token;
	t_token *tmp;
	t_err	st;

	// split_token = NULL;
	*new_tokens = NULL;
	last_new = NULL;
	tmp = token;
	while (tmp)
	{
		st = word_split_token(tmp, mini, &split_token);
		if (st == ERR_MALLOC)
		{
			puterr(ft_sprintf(": error: Memory allocation error\n"), false);
			free_tokens(token);
			if (*new_tokens)
				free_tokens(*new_tokens);
			free_env(&mini->env);
			exit(EXIT_FAILURE);
		}
		// (void)mini;
		// split_token = NULL;
		if (split_token == NULL)
		{
			tmp = tmp->next;
			continue;
			// puterr(ft_sprintf(": error: Memory allocation error\n"),
			// 	   false);
			// free_tokens(token);
			// if (*new_tokens)
			// 	free_tokens(*new_tokens);
			// free_env(&mini->env);
			// exit(EXIT_FAILURE);
		}
		if (!*new_tokens)
			*new_tokens = split_token;
		else
			last_new->next = split_token;

		last_new = get_tail(split_token);
		tmp = tmp->next;
	}
}
