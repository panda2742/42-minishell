/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:39:25 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/10 10:45:05 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BASE_H
# define FT_BASE_H

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

# define B_BLACK "\033[1;30m"
# define B_RED "\033[1;31m"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[1;33m"
# define B_BLUE "\033[1;34m"
# define B_MAGENTA "\033[1;35m"
# define B_CYAN "\033[1;36m"
# define B_WHITE "\033[1;37m"

# define U_BLACK "\033[4;30m"
# define U_RED "\033[4;31m"
# define U_GREEN "\033[4;32m"
# define U_YELLOW "\033[4;33m"
# define U_BLUE "\033[4;34m"
# define U_MAGENTA "\033[4;35m"
# define U_CYAN "\033[4;36m"
# define U_WHITE "\033[4;37m"

typedef enum e_bool
{
	false,
	true
}	t_bool;

#endif