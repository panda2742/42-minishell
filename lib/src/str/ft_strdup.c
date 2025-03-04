/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:04:49 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/06 21:04:49 by elouannh         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_str.h"

char	*ft_strdup(const char *s1)
{
	int		slen;
	int		i;
	char	*result;

	slen = ft_strlen(s1);
	result = (char *)malloc((slen + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
