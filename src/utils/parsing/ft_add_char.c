/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:11:01 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/23 16:25:33 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Callled in expand_tokens.c and expand
*/
void	handle_normal_char(t_utils *utils, char *input)
{
	char	tmp[2];

	tmp[0] = input[utils->i];
	tmp[1] = '\0';
	utils->s1 = str_join_free(utils->s1, tmp);
	utils->i++;
}

void	add_char_to_string(char *expanded, char **current, int *i)
{
	char	tmp[2];

	tmp[0] = expanded[*i];
	tmp[1] = '\0';
	*current = str_join_free(*current, tmp);
	(*i)++;
}
