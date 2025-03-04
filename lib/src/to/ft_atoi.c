/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:23:09 by ehosta            #+#    #+#             */
/*   Updated: 2024/11/06 11:23:09 by ehosta           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_to.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	long	n;
	int		sign;

	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	n = 0;
	while (ft_isdigit(str[i]))
	{
		if ((n * 10 + str[i] - '0') / 10 != n)
			return (LONG_MAX * (sign > 0) + LONG_MIN * (sign < 0));
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n * sign);
}
