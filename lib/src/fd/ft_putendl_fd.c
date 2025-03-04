/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:45:09 by ehosta            #+#    #+#             */
/*   Updated: 2025/01/15 13:45:09 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_fd.h"

ssize_t	ft_putendl_fd(char *s, int fd)
{
	int	putstr_result;
	int	newline_result;

	putstr_result = ft_putstr_fd(s, fd);
	if (putstr_result == -1)
		return (-1);
	newline_result = ft_putchar_fd('\n', fd);
	if (newline_result == -1)
		return (-1);
	return (putstr_result + newline_result);
}
