/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:11:01 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/09 14:05:43 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Callled in expand_tokens.c and expand
*/
t_err	handle_normal_char(t_utils *utils, char *input)
{
	char	tmp[2];
	char	*new;

	tmp[0] = input[utils->i];
	tmp[1] = '\0';
	new = str_join_free(utils->s1, tmp);
	if (new == NULL)
		return (ERR_MALLOC);
	utils->s1 = new;
	utils->i++;
	return (ERR_NONE);
}

t_err	add_char_to_string(char *expanded, char **current, int *i)
{
	char	tmp[2];
	char	*new;

	tmp[0] = expanded[*i];
	tmp[1] = '\0';
	new = str_join_free(*current, tmp);
	if (new == NULL)
		return (ERR_MALLOC);
	*current = new;
	(*i)++;
	return (ERR_NONE);
}
