/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:45:35 by ehosta            #+#    #+#             */
/*   Updated: 2025/01/15 13:45:35 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_fd.h"

ssize_t	ft_putptr_fd(unsigned long long n, int fd)
{
	int	putnbr_result;

	if (n == 0)
	{
		if (ft_putstr_fd("(nil)", fd) == -1)
			return (-1);
		return (5);
	}
	if (ft_putstr_fd("0x", fd) == -1)
		return (-1);
	putnbr_result = ft_putnbr_base_fd(n, "0123456789abcdef", fd);
	if (putnbr_result == -1)
		return (-1);
	return (2 + putnbr_result);
}
