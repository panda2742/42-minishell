/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:34 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/12 15:18:51 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*get_var(t_env_manager *env, const char *name)
{
	size_t		i;
	t_env_var	*var;

	i = -1;
	var = *env->vars;
	while (++i < env->env_size && var)
	{
		if (ft_strcmp((char *)name, var->name) == 0)
		{
			return (var);
		}
		var = var->next;
	}
	return (NULL);
}
