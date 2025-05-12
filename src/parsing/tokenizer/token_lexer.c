/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:03:27 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/12 15:46:53 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token		*tmp_token;
	t_fragment	*tmp_frag;
	t_fragment	*next_frag;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp_token = tokens;
		tokens = tokens->next;
		tmp_frag = tmp_token->fragments;
		while (tmp_frag)
		{
			next_frag = tmp_frag->next;
			free(tmp_frag->text);
			free(tmp_frag);
			tmp_frag = next_frag;
		}
		free(tmp_token);
	}
}

t_token	*ft_create_token(t_token_type type)
{
	t_token	*new;

	new = ft_memalloc(sizeof(t_token));
	// new = NULL;
	if (!new)
		return (NULL);
	new->is_first_word = false;
	new->type = type;
	new->fragments = NULL;
	new->text = NULL;
	new->next = NULL;
	return (new);
}

void	append_token(t_token **token_list, t_token *token)
{
	t_token	*tmp;

	if (!(*token_list))
		*token_list = token;
	else
	{
		tmp = *token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}
