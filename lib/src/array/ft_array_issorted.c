/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_issorted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:43:25 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/20 17:55:51 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

t_bool	ft_array_issorted(t_array *arr)
{
	int	i;

	i = -1;
	while (++i < arr->size - 1)
	{
		if (ft_array_getval(arr, arr->head, i)
			> ft_array_getval(arr, arr->head, i + 1))
			return (false);
	}
	return (true);
}
