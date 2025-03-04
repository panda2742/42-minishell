/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:45:52 by ehosta            #+#    #+#             */
/*   Updated: 2024/12/04 11:45:52 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IS_H
# define FT_IS_H

# include "ft_base.h"

/**
 * Returns 1 if the caracter is an alphanumeric value. It means the value is
 * an alpha or a digit.
 * @param c The character to check.
 * @return Returns 1 if the character passes the condition, 0 otherwise.
 */
t_bool	ft_isalnum(int c);

/**
 * Returns 1 if the caracter is an alpha character (in [65, 90] or in
 * [97, 122]).
 * @param c The character to check.
 * @return Returns 1 if the character passes the condition, 0 otherwise.
 */
t_bool	ft_isalpha(int c);

/**
 * Returns 1 if the caracter is an ascii character (in [0, 127]).
 * @param c The character to check.
 * @return Returns 1 if the character passes the condition, 0 otherwise.
 */
t_bool	ft_isascii(int c);

/**
 * Returns 1 if the caracter is a digit character (in [48, 57]).
 * @param c The character to check.
 * @return Returns 1 if the character passes the condition, 0 otherwise.
 */
t_bool	ft_isdigit(int c);

t_bool	ft_isincharset(char c, const char *charset);

/**
 * Returns 1 if the caracter is a printable character (in [32, 127[).
 * @param c The character to check.
 * @return Returns 1 if the character passes the condition, 0 otherwise.
 */
t_bool	ft_isprint(int c);

t_bool	ft_issorted(int *tab, int size);

#endif
