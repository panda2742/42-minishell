/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:01:09 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/23 14:46:40 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function returns the first word in a token list.
 * It is used to set the cmd name in the t_excmd struct.
 * Set the is_first_word flag to true so we know it is not a common word.
*/
char	*get_first_word(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
		{
			tmp->is_first_word = true;
			return (tmp->text);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
