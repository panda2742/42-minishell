/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:04:33 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/06 21:04:33 by elouannh         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_mem.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dststr;
	unsigned char	*srcstr;
	size_t			i;

	dststr = (unsigned char *)dst;
	srcstr = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	i = 0;
	while (i < n)
	{
		dststr[i] = srcstr[i];
		i++;
	}
	return (dst);
}
