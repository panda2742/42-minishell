/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:37:35 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/10 14:08:28 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

void	ft_array_clear(t_array *arr)
{
	if (!arr)
		return ;
	if (arr->type == ARRAY_INT)
		ft_free_inttab(arr->data);
	if (arr->type == ARRAY_STRING)
		ft_free_strtab(arr->data);
	arr->size = 0;
	arr->head = 0;
	arr->id = 0;
	free(arr);
}
