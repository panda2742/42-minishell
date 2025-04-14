/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:34 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:02:15 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*get_var(t_env_manager *env, const char *name)
{
	size_t		i;
	t_env_var	*var;

	i = -1;
	var = *env->vars;
	while (++i < env->env_size && var->next)
	{
		if (ft_strncmp(name, var->name, ft_strlen(var->name)) == 0)
			return (var);
		var = var->next;
	}
	return (NULL);
}
