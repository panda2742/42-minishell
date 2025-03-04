/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_popint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:36:56 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/10 18:06:03 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

int	ft_array_popint(t_array *arr, int pos)
{
	int	*tab;
	int	elt;
	int	i;

	if (arr->type != ARRAY_INT)
		return (0);
	tab = (int *)arr->data;
	elt = tab[pos];
	if (arr->head + 1 == arr->size)
	{
		arr->size -= 1;
		arr->head = 0;
		return (elt);
	}
	i = arr->head - 1;
	while (++i + 1 < arr->size)
		tab[i] = tab[i + 1];
	tab[i] = 0;
	arr->size -= 1;
	return (elt);
}
