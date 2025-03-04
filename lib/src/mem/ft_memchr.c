/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:04:29 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/08 14:45:41 by ehosta           ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_mem.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr = (const unsigned char *)s;

	while (n > 0)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
