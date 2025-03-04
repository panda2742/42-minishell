/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:45:23 by ehosta            #+#    #+#             */
/*   Updated: 2025/01/15 13:45:23 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_fd.h"

ssize_t	ft_putnbr_base_fd(double long n, char *base, int fd)
{
	int		recur_result;
	size_t	baselen;

	if (n < 0)
	{
		if (ft_putchar_fd('-', fd) == -1)
			return (-1);
		recur_result = ft_putnbr_base_fd(-n, base, fd);
		if (recur_result == -1)
			return (-1);
		return (1 + recur_result);
	}
	baselen = ft_strlen(base);
	if (n >= baselen)
	{
		recur_result = ft_putnbr_base_fd(n / baselen, base, fd);
		if (recur_result == -1)
			return (-1);
		return (recur_result + ft_putchar_fd(base[((int)n % baselen)], fd));
	}
	return (ft_putchar_fd(base[(int)n], fd));
}
