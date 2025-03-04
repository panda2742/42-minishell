/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:05:15 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/06 21:05:15 by elouannh         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_str.h"

static size_t	_getmax(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (start >= ft_strlen(s))
	{
		res = (char *)malloc(sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	res = (char *)malloc((_getmax(s, start, len) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static size_t	_getmax(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && s[start + i])
		i++;
	return (i);
}
