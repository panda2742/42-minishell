/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:02:06 by ehosta            #+#    #+#             */
/*   Updated: 2024/12/04 12:02:06 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TO_H
# define FT_TO_H

# include <stdlib.h>
# include <limits.h>
# include "ft_is.h"
# include "ft_str.h"

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_toupper(int c);
int		ft_tolower(int c);

#endif
