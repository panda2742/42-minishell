/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:42:32 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 13:42:33 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
 * Create a fragment.
 * Fragments are multiple quotes one after the other
 * ex: $USER$PATH
 * USER is frag 1, PATH is frag 2
 */

t_fragment	*new_fragment(const char *start, size_t len, t_qtype quote_type)
{
	t_fragment	*new;

	new = malloc(sizeof(t_fragment));
	if (!new)
		return (NULL);
	new->text = malloc(sizeof(char) * (len + 1));
	if (!new->text)
	{
		free(new);
		return (NULL);
	}
	ft_memcpy(new->text, start, len);
	new->text[len] = '\0';
	new->quote_type = quote_type;
	new->next = NULL;
	return (new);
}

/*
 * Add frag at the end of the list
 */
void	append_fragment(t_token *token, t_fragment *frag)
{
	t_fragment	*tmp;

	if (!token->fragments)
		token->fragments = frag;
	else
	{
		tmp = token->fragments;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = frag;
	}
}
