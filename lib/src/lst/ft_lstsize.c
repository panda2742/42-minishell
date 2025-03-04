/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:39:32 by ehosta            #+#    #+#             */
/*   Updated: 2024/11/13 11:39:32 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_lst.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*t;
	int		i;

	i = 0;
	if (!lst)
		return (0);
	t = lst;
	i++;
	while (t)
	{
		if (!t->next)
			return (i);
		t = t->next;
		i++;
	}
	return (i);
}
