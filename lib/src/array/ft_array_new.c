/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:37:37 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/11 10:47:57 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

t_array	*ft_array_new(char id, int size, t_array_type type)
{
	t_array	*arr;
	size_t	bytes;

	arr = malloc(sizeof(t_array));
	if (!arr)
		return (NULL);
	arr->id = id;
	arr->size = size;
	arr->type = type;
	arr->head = 0;
	bytes = 0;
	if (type == ARRAY_INT)
		bytes = sizeof(int) * size;
	if (type == ARRAY_STRING)
		bytes = sizeof(char **) * (size + 1);
	arr->data = malloc(bytes);
	if (!arr->data)
		return (free(arr), NULL);
	return (arr);
}
