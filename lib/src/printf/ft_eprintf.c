/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:12:30 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/25 10:16:13 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_eprintf(const char *format, ...)
{
	va_list	args;
	int		return_value;

	if (!format || !*format)
		return (-1);
	va_start(args, format);
	return_value = parse_format((char *)format, args, 2);
	va_end(args);
	return (return_value);
}
