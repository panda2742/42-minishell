/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_getpos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:25:05 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/11 23:18:05 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

int	ft_array_getpos(t_array *arr, int val)
{
	int	*tab;
	int	i;

	if (arr->type != ARRAY_INT)
		return (0);
	tab = (int *)arr->data;
	i = -1;
	while (++i < arr->size)
		if (tab[i] == val)
			return (i);
	return (i);
}
