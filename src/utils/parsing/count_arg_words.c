/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arg_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:29:55 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/17 10:50:43 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (tmp->type == WORD)
			nb_of_words++;
		tmp = tmp->next;
	}
	return (nb_of_words);
}
