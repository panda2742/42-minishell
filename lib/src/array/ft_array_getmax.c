/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_getmax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:35:25 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/13 14:36:43 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

int	ft_array_getmax(t_array *arr)
{
	int	*tab;
	int	max;
	int	i;

	tab = ((int *)arr->data);
	max = -1;
	i = -1;
	while (++i < arr->size)
	{
		if (tab[i] > max)
			max = tab[i];
	}
	return (max);
}
