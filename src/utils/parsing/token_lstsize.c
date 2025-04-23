/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lstsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:15:36 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/23 14:49:23 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * To calculate argc
*/
size_t	token_lstsize(t_token *head)
{
	t_token	*tmp;
	size_t	size;

	size = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
			size++;
		tmp = tmp->next;
	}
	return (size);
}
