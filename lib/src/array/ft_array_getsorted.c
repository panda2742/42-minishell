/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_getsorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:59:12 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/10 12:43:20 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

t_array	*ft_array_getsorted(t_array *arr, t_bool replace_by_index)
{
	t_array	*sorted;
	int		*arrtab;
	int		*sortedtab;
	int		i;

	if (arr->type != ARRAY_INT)
		return (0);
	sorted = ft_array_new('s', arr->size, arr->type);
	if (!sorted)
		return (NULL);
	arrtab = (int *)arr->data;
	sortedtab = (int *)sorted->data;
	i = -1;
	while (++i < arr->size)
		sortedtab[i] = arrtab[i];
	ft_selection_sort(sortedtab, sorted->size);
	i = -1;
	while (++i < arr->size)
	{
		if (replace_by_index)
			arrtab[ft_array_getpos(arr, sortedtab[i])] = i;
		sortedtab[i] = i;
	}
	return (sorted);
}
