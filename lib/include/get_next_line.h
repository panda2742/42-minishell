/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:14:09 by ehosta            #+#    #+#             */
/*   Updated: 2025/01/15 17:30:45 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_mem.h"
# include "ft_str.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 65536
# endif

/**
 * Read a single line of a given file descriptor. Can read multiple file
 * descriptor simultaneously and statically. You need to open and close the
 * file yourself.
 * @param fd The file descriptor to read.
 * @returns The alloc'd read line. If an error occurs or if the file is
 * finished, NULL is returned instead.
 */
char	*get_next_line(int fd);

#endif