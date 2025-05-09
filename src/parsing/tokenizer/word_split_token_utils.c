/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_token_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:07:12 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/09 11:08:26 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_err	free_n_list(t_w_split *n_list)
{
	if (n_list->current)
	{
		free(n_list->current);
		n_list->current = NULL;
	}
	if (n_list->new_h)
	{
		free_tokens(n_list->new_h);
	}
	n_list->new_h = NULL;
	n_list->new_t = NULL;
	return (ERR_MALLOC);
}

t_err	set_n_list_and_frag(t_w_split *n_list)
{
	n_list->new_h = NULL;
	n_list->new_t = NULL;
	n_list->current = NULL;
	n_list->has_quotes = false;
	n_list->current = ft_strdup("");
	if (!n_list->current)
	{
		return (ERR_MALLOC);
	}
	return (ERR_NONE);
}


t_err	empty_var(t_w_split *n_list, t_token **out_list)
{
	free(n_list->current);
	n_list->current = NULL;
	*out_list = n_list->new_h;
	return (ERR_NONE);
}