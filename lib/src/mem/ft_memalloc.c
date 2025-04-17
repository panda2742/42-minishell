/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:09 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/17 10:16:03 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_mem.h"

#include <stdio.h>

void	*ft_memalloc(size_t __size)
{
	static int	crash = 0;

	(void)crash;
	// if (crash++ > -10)
	// 	return (NULL);
	return (malloc(__size));
}
