/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_getmin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:05:55 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/13 14:12:26 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

int	ft_array_getmin(t_array *arr)
{
	int	*tab;
	int	min;
	int	i;

	tab = ((int *)arr->data);
	min = 65000;
	i = -1;
	while (++i < arr->size)
	{
		if (tab[i] < min)
			min = tab[i];
	}
	return (min);
}
