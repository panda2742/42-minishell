/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:43:25 by ehosta            #+#    #+#             */
/*   Updated: 2024/12/04 11:43:25 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FD_H
# define FT_FD_H

# include <unistd.h>
# include "ft_str.h"

/**
 * Writes a character (type char -128 to 127) in the given file descriptor.
 * @param c The character to write.
 * @param fd The file descriptor to write in.
 * @return Returns 1 if the character has been written, or -1 if an error
 * occurs.
 */
ssize_t	ft_putchar_fd(char c, int fd);

/**
 * Writes a sequence of characters (a string) and adds a newline at the end of
 * it in the given file descriptor. If an error occurs while the function
 * writes each character, the function exits.
 * @param s The string to write.
 * @param fd The file descriptor to write in.
 * @return Returns the total length of the written string (including the 
 * newline caracter), or -1 if an error occurs.
 */
ssize_t	ft_putendl_fd(char *s, int fd);

/**
 * Writes a number into the given file descriptor. The parameter could be any
 * integer or floating value, as the type is the largest possible. Please
 * manage your overflows with a cast. If an error occurs while the function
 * writes each digit, the function exits.
 * @param n The number to write.
 * @param base The base (a string) to write the given number with.
 * @param fd The file descriptor to write in.
 * @return Returns the amount of written digits, or -1 if an error occurs.
 */
ssize_t	ft_putnbr_base_fd(long double n, char *base, int fd);

/**
 * Writes a integer (type int) into the given file descriptor. If an error
 * occurs while the function writes each digit, the function exits.
 * @param n The integer to write.
 * @param fd The file descriptor to write in.
 * @return Returns the amount of written digits, or -1 if an error occurs.
 */
ssize_t	ft_putnbr_fd(int n, int fd);

/**
 * Writes a pointer address to the given file descriptor. It is basically a
 * ft_putnbr_base_fd(3) call with an hexadecimal base, handling the NULL case
 * and adding the 0x at the start. If an error occurs while the function writes
 * each character, the function exits.
 * @param n The pointer address (type unsigned long long) to write.
 * @param fd The file descriptor to write in.
 * @return Returns the amount of written characters, or -1 if an error occurs.
 */
ssize_t	ft_putptr_fd(unsigned long long n, int fd);

/**
 * Writes a sequence of characters (a string) in the given file descriptor.
 * If an error occurs while the function writes each character, the function
 * exits.
 * @param s The string to write.
 * @param fd The file descriptor to write in.
 * @return Returns the amount of written characters, or -1 if an error occurs.
 */
ssize_t	ft_putstr_fd(char *s, int fd);

#endif
