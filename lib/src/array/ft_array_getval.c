/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_getval.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:25:08 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/11 16:08:30 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

int	ft_array_getval(t_array *arr, int pos, int offset)
{
	int	sign;
	int	*tab;

	if (arr->type != ARRAY_INT)
		return (0);
	sign = ft_sign(offset);
	while (offset)
	{
		pos += sign;
		if (pos < 0)
			pos = arr->size - 1;
		if (pos >= arr->size)
			pos = 0;
		offset -= sign;
	}
	tab = (int *)arr->data;
	return (tab[pos]);
}
