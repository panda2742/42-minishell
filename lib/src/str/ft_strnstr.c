/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:05:09 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/06 21:05:09 by elouannh         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_str.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	llen;
	size_t	i;
	size_t	c;
	char	*bigcpy;

	llen = ft_strlen(little);
	if (!llen)
		return ((char *)big);
	if (!len)
		return (NULL);
	bigcpy = (char *)big;
	i = 0;
	while (bigcpy[i] && i < len)
	{
		c = 0;
		while (bigcpy[i + c] && little[c]
			&& bigcpy[i + c] == little[c] && i + c < len)
			c++;
		if (c == llen)
			return (bigcpy + i);
		i++;
	}
	return (NULL);
}
