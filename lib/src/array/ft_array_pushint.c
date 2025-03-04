/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_pushint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:57:05 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/11 11:17:58 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

t_array	*ft_array_pushint(t_array *arr, int elt)
{
	int	i;
	int	*tab;

	if (arr->type != ARRAY_INT)
		return (0);
	tab = (int *)arr->data;
	arr->size += 1;
	i = arr->size - 1;
	while (i > arr->head)
	{
		tab[i] = tab[i - 1];
		i--;
	}
	tab[arr->head] = elt;
	return (arr);
}
