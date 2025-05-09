/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:25 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/09 12:03:11 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_unset_var(t_excmd *c, int i);

t_exit	builtin_unset(t_excmd *c)
{
	int	i;

	if (c->argc == 1)
	{
		puterr(ft_sprintf(": %s: Too few arguments\n", c->name), false);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (++i < c->argc)
		_unset_var(c, i);
	return (0);
}

static void	_unset_var(t_excmd *c, int i)
{
	t_env_var	*var;
	t_env_var	*prev;

	var = *c->env->vars;
	prev = NULL;
	while (var)
	{
		if (ft_strncmp(var->name, c->argv[i], ft_strlen(var->name)) == 0)
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
		else
			break ;
	}
}
