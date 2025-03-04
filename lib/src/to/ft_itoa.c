/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:04:27 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/08 15:42:20 by ehosta           ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_to.h"

static int	_digits_size(int n);
static void	_reverse_str(char *str);

char	*ft_itoa(int n)
{
	char	*buf;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	buf = (char *)malloc(sizeof(char) * (_digits_size(n) + 1));
	if (!buf)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		n *= -1;
		buf[i++] = '-';
	}
	while (n)
	{
		buf[i++] = n % 10 + '0';
		n /= 10;
	}
	buf[i] = '\0';
	_reverse_str(buf);
	return (buf);
}

static int	_digits_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	_reverse_str(char *str)
{
	char	t;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(str) - 1;
	if (str[start] == '-')
		start++;
	while (str[start] && start < end)
	{
		t = str[start];
		str[start] = str[end];
		str[end] = t;
		start++;
		end--;
	}
}
