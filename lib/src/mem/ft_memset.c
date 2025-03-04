/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:06:02 by ehosta            #+#    #+#             */
/*   Updated: 2024/11/06 12:06:02 by ehosta           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_mem.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*sstr;

	sstr = (unsigned char *)b;
	while (len > 0)
	{
		sstr[len - 1] = (unsigned char)c;
		len--;
	}
	return (b);
}
