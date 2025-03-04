/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:58:33 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/10 12:24:10 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

static void	_fill_itoi(t_array *arr, int val, int i);

t_array	*ft_array_fill(t_array *arr, void *content, t_array_type content_type)
{
	int	i;

	i = -1;
	while (++i < arr->size)
	{
		if (arr->type == ARRAY_INT && content_type == ARRAY_INT)
			_fill_itoi(arr, ((int *)content)[i], i);
		else if (arr->type == ARRAY_INT && content_type == ARRAY_STRING)
			_fill_itoi(arr, ft_atoi(((char **)content)[i]), i);
	}
	return (arr);
}

static void	_fill_itoi(t_array *arr, int val, int i)
{
	int	*arrtab;

	arrtab = (int *)arr->data;
	arrtab[i] = val;
}
