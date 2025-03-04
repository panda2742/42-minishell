/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:04:20 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/06 21:04:20 by elouannh         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_mem.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes;
	void	*ptr;

	bytes = count * size;
	if (count != 0 && (count * size) / count != size)
		return (NULL);
	ptr = malloc(bytes);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, bytes);
	return (ptr);
}
