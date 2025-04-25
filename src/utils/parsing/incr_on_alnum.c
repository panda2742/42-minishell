/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incr_on_alnum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:02:43 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/23 14:48:23 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function increments the index j until it finds a non-alphanumeric
*/

void	incr_on_alnum(char *str, int *j)
{
	while (str[*j] && ft_isalnum(str[*j]))
		(*j)++;
}
