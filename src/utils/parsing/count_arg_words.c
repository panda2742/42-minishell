/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arg_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:29:55 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/23 14:43:28 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Count the number of TOKEN_WORD in a token list.
 * Called when we set argc
 */

size_t	count_arg_words(t_token *token)
{
	t_token	*tmp;
	size_t	nb_of_words;

	tmp = token;
	nb_of_words = 0;
	if (!token)
		return (0);
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
			nb_of_words++;
		tmp = tmp->next;
	}
	return (nb_of_words);
}
