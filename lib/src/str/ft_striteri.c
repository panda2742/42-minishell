/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:04:51 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/06 21:04:51 by elouannh         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_str.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	size_t			slen;

	i = 0;
	slen = ft_strlen(s);
	while (i < slen)
	{
		f(i, &s[i]);
		i++;
	}
}
