/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:39 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:19:43 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env_manager *env)
{
	size_t		i;
	t_env_var	*var;
	t_env_var	*next;

	i = -1;
	var = *env->vars;
	while (++i < env->env_size && var->next)
	{
		next = var->next;
		free(var->name);
		free(var->value);
		free(var);
		var = next;
	}
	free(var->name);
	free(var->value);
	free(var);
	free(env->vars);
}
