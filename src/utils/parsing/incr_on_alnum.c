/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incr_on_alnum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:02:43 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/09 18:05:47 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function increments the index j until it finds a non-alphanumeric
*/

void	incr_on_alnum(char *str, int *j, int i)
{
	*j = i;
	while (str[*j] && ft_isalnum(str[*j]))
		(*j)++;
}
