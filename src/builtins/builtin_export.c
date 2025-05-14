/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:21 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 09:31:24 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exit	_no_args(t_excmd *c);
static t_bool	_write_var(t_excmd *cmd, t_env_var *var);
static t_bool	_write_var_value(t_excmd *cmd, t_env_var *var);

t_exit	builtin_export(t_excmd *c)
{
	if (c->argc == 1)
		return (_no_args(c));
	printf("%s\n", c->argv[1]);
	return (EXIT_SUCCESS);
}

static t_exit	_no_args(t_excmd *c)
{
	size_t		i;
	t_env_var	**vars;
	t_env_var	*var;

	i = -1;
	vars = dup_env_vars(c->env);
	if (!vars)
		return (EXIT_FAILURE);
	sort_env_list(vars);
	var = *vars;
	while (++i < c->env->env_size && var)
	{
		if (!var->name)
		{
			var = var->next;
			continue ;
		}
		if (!_write_var(c, var))
		{
			free_dup_vars(vars);
			return (EXIT_FAILURE);
		}
		var = var->next;
	}
	free_dup_vars(vars);
	return (EXIT_SUCCESS);
}

static t_bool	_write_var(t_excmd *cmd, t_env_var *var)
{
	t_bool	is_last;

	is_last = display_colors(cmd);
	if (is_last)
	{
		if (write(1, BLACK, 5) == -1)
			return (false);
	}
	if (write(1, "export ", 7) == -1)
		return (false);
	if (is_last)
	{
		if (write(1, RESET, 5) == -1)
			return (false);
		if (write(1, B_YELLOW, 7) == -1)
			return (false);
	}
	if (write(1, var->name, var->name_length) == -1)
		return (false);
	return (_write_var_value(cmd, var));
}

static t_bool	_write_var_value(t_excmd *cmd, t_env_var *var)
{
	t_bool	is_last;

	is_last = display_colors(cmd);
	if (is_last)
	{
		if (write(1, RESET, 5) == -1)
			return (false);
	}
	if (write(1, "=\"", 2) == -1)
		return (false);
	if (write(1, var->value, ft_strlen(var->value)) == -1)
		return (false);
	if (write(1, "\"\n", 2) == -1)
		return (false);
	return (true);
}
