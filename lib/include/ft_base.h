/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:39:25 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/15 11:27:17 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BASE_H
# define FT_BASE_H

# define BLACK "\001\033[30m\002"
# define RED "\001\033[31m\002"
# define GREEN "\001\033[32m\002"
# define YELLOW "\001\033[33m\002"
# define BLUE "\001\033[34m\002"
# define MAGENTA "\001\033[35m\002"
# define CYAN "\001\033[36m\002"
# define WHITE "\001\033[37m\002"
# define RESET "\001\033[0m\002"

# define B_BLACK "\001\033[1;30m\002"
# define B_RED "\001\033[1;31m\002"
# define B_GREEN "\001\033[1;32m\002"
# define B_YELLOW "\001\033[1;33m\002"
# define B_BLUE "\001\033[1;34m\002"
# define B_MAGENTA "\001\033[1;35m\002"
# define B_CYAN "\001\033[1;36m\002"
# define B_WHITE "\001\033[1;37m\002"

# define U_BLACK "\001\033[4;30m\002"
# define U_RED "\001\033[4;31m\002"
# define U_GREEN "\001\033[4;32m\002"
# define U_YELLOW "\001\033[4;33m\002"
# define U_BLUE "\001\033[4;34m\002"
# define U_MAGENTA "\001\033[4;35m\002"
# define U_CYAN "\001\033[4;36m\002"
# define U_WHITE "\001\033[4;37m\002"

typedef enum e_bool
{
	false,
	true
}	t_bool;

#endif