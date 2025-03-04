/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouannh <ehosta@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:04:43 by elouannh          #+#    #+#             */
/*   Updated: 2024/11/06 21:04:43 by elouannh         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_fd.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}
