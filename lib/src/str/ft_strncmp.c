/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:05:07 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/06 21:05:07 by elouannh         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_str.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n)
	{
		if (!*s1)
		{
			if (!*s2)
				return (0);
			return (-(unsigned char)*s2);
		}
		if (!*s2)
			return ((unsigned char)*s1);
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
