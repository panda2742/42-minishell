/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:16 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/12 14:33:04 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	_write_var(t_excmd *cmd, t_env_var *var);
static t_bool	_is_last(t_excmd *cmd);

t_exit	builtin_env(t_excmd *c)
{
	size_t		i;
	t_env_var	*var;

	i = -1;
	var = *c->env->vars;
	while (++i < c->env->env_size && var)
	{
		if (!var->name || !var->value)
		{
			var = var->next;
			continue ;
		}
		if (!_write_var(c, var))
			return (EXIT_FAILURE);
		var = var->next;
	}
	return (EXIT_SUCCESS);
}

static t_bool	_write_var(t_excmd *cmd, t_env_var *var)
{
	t_bool	is_last;

	is_last = _is_last(cmd);
	if (is_last)
	{
		if (write(1, U_BLUE, 7) == -1)
			return (false);
	}
	if (write(1, var->name, var->name_length) == -1)
		return (false);
	if (is_last)
	{
		if (write(1, RESET, 5) == -1)
			return (false);
	}
	if (write(1, "=", 1) == -1)
		return (false);
	if (write(1, var->value, ft_strlen(var->value)) == -1)
		return (false);
	if (write(1, "\n", 1) == -1)
		return (false);
	return (true);
}

static t_bool	_is_last(t_excmd *cmd)
{
	return (cmd->next == NULL && cmd->out_redirects.size == 0);
}
