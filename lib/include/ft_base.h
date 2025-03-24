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

# if defined(__APPLE__)
# define RED ""
# define GREEN ""
# define YELLOW ""
# define BLUE ""
# define MAGENTA ""
# define CYAN ""
# define RESET ""
# define GRAY ""
# endif

# ifndef RED
# define RED "\033[31m"
# endif

# ifndef GREEN
# define GREEN "\033[32m"
# endif

# ifndef YELLOW
# define YELLOW "\033[33m"
# endif

# ifndef BLUE
#  define BLUE "\033[34m"
# endif

# ifndef MAGENTA
# define MAGENTA "\033[35m"
# endif

# ifndef CYAN
# define CYAN "\033[36m"
# endif

# ifndef RESET
#  define RESET "\033[0m"
# endif

# ifndef GRAY
#  define GRAY "\033[37m"
# endif

typedef enum e_bool
{
	false,
	true
}	t_bool;

#endif