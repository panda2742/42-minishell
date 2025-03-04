/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isincharset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:54:12 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/19 15:55:31 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_is.h"

t_bool	ft_isincharset(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (true);
		charset++;
	}
	return (false);
}
