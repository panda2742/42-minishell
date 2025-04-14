/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:25 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:00:26 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_unset_var(t_excmd *c);

t_exit	builtins_unset(t_excmd *c)
{
	if (c->argc > 2)
		return (
			command_failure(
				c, ft_sprintf(": %s: Too many arguments\n", c->name), false
			)
		);
	if (c->argc == 1)
		return (
			command_failure(
				c, ft_sprintf(": %s: Too few arguments\n", c->name), false
			)
		);
	_unset_var(c);
	return (0);
}

static void	_unset_var(t_excmd *c)
{
	t_env_var	*var;
	t_env_var	*prev;

	var = *c->env->vars;
	prev = NULL;
	while (var)
	{
		if (ft_strncmp(var->name, c->argv[1], ft_strlen(var->name)) == 0)
		{
			if (!prev)
				c->env->vars[0] = var->next;
			else
				prev->next = var->next;
			free(var->name);
			free(var->value);
			free(var);
			c->env->env_size -= 1;
			break ;
		}
		prev = var;
		if (var->next)
			var = var->next;
	}
}
