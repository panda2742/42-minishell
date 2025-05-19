/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:12:21 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/19 11:01:57 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*ensure_var(t_env_manager *env, const char *name,
				char *default_val)
{
	t_env_var	*var;

	var = get_var(env, name);
	if (var == NULL)
		return (NULL);
	if (var->value)
	{
		free(default_val);
		return (var);
	}
	var->value = ft_strdup(default_val);
	free(default_val);
	var->value_length = ft_strlen(var->value);
	return (var);
}

t_env_var	*init_var(t_env_manager *env, const char *name)
{
	t_env_var	*var;
	t_env_var	*last;

	var = ft_memalloc(sizeof(t_env_var));
	if (var == NULL)
		return (NULL);
	var->name = ft_strdup(name);
	var->name_length = ft_strlen(var->name);
	var->value = NULL;
	var->value_length = 0;
	var->next = NULL;
	last = *env->vars;
	if (last == NULL)
	{
		env->vars[0] = var;
		env->env_size++;
		return (var);
	}
	while (last->next)
		last = last->next;
	last->next = var;
	env->env_size++;
	return (var);
}

t_bool	var_exists(t_env_manager *env, char *name)
{
	t_env_var	*var;

	var = get_var(env, name);
	return (var != NULL);
}
