/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:57:27 by ehosta            #+#    #+#             */
/*   Updated: 2024/11/06 11:57:27 by ehosta           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_mem.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr++ = '\0';
		n--;
	}
}
