/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:07:56 by ehosta            #+#    #+#             */
/*   Updated: 2024/12/16 18:07:56 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "ft_fd.h"

# ifndef PRINTF_FD
#  define PRINTF_FD 1
# endif

int	ft_printf(const char *format, ...);
int	ft_eprintf(const char *format, ...);
int	parse_format(char *str, va_list args, int fd);

#endif
