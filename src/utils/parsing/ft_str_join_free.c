/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_join_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:26:35 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/23 14:44:19 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Join but also free the first string.
*/
static void	set_len(t_utils *vars, char *s1, const char *s2)
{
	if (s1)
		vars->len1 = ft_strlen(s1);
	if (s2)
		vars->len2 = ft_strlen(s2);
}

char	*str_join_free(char *s1, const char *s2)
{
	char	*new;
	t_utils	vars;

	ft_memset(&vars, 0, sizeof(t_utils));
	set_len(&vars, s1, s2);
	new = ft_memalloc(vars.len1 + vars.len2 + 1);
	if (!new)
		return (free_str_return_null(s1));
	while (vars.i < vars.len1)
	{
		new[vars.i] = s1[vars.i];
		vars.i++;
	}
	while (vars.j < vars.len2)
	{
		new[vars.i++] = s2[vars.j];
		vars.j++;
	}
	new[vars.i] = '\0';
	free(s1);
	return (new);
}
