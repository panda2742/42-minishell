/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lstsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:15:36 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/10 11:32:50 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	token_lstsize(t_token *head)
{
	t_token	*tmp;
	size_t	size;
	
	size = 0;
	tmp = head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
