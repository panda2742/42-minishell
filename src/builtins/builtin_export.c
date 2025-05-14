/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:21 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 13:54:52 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exit	_no_args(t_excmd *c);
static t_bool	_write_var(t_excmd *cmd, t_env_var *var);
static t_bool	_write_var_value(t_excmd *cmd, t_env_var *var);
static void	_do_op(t_env_manager *env, char *str);

t_exit	builtin_export(t_excmd *c)
{
	int	i;

	if (c->argc == 1)
		return (_no_args(c));
	i = 1;
	while (i < c->argc)
	{
		_do_op(c->env, c->argv[i]);
		i++;
	}
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
	if (var->value)
	{
		if (write(1, "=\"", 2) == -1)
			return (false);
		if (write(1, var->value, ft_strlen(var->value)) == -1)
			return (false);
		if (write(1, "\"", 2) == -1)
			return (false);
	}
	if (write(1, "\n", 2) == -1)
		return (false);
	return (true);
}

static void	_do_op(t_env_manager *env, char *str)
{
	char			*identifier;
	unsigned char	op;
	char			*value;
	t_env_var		*var;
	t_env_var		*new_var;
	t_env_var		*last;
	char			*new_value;

	identifier = get_identifier(str);
	if (valid_identifier_name(identifier) == false)
	{
		puterr(ft_sprintf(": export: `%s': not a valid identifier\n", identifier), false);
		return (free(identifier));
	}
	op = get_operation(str);
	if (op == 3)
		return (free(identifier));
	value = get_value(str);
	var = get_var(env, identifier);
	if (var == NULL)
	{
		new_var = ft_memalloc(sizeof(t_env_var));
		if (new_var == NULL)
		{
			free(identifier);
			return ((void)puterr(ft_strdup(": Memory allocation error\n"), false));
		}
		new_var->name = ft_strdup(identifier);
		free(identifier);
		new_var->name_length = ft_strlen(new_var->name);
		new_var->next = NULL;
		if (op == 0)
		{
			new_var->value = NULL;
			new_var->value_length = 0;
		}
		else
		{
			new_var->value = ft_strdup(value);
			new_var->value_length = ft_strlen(new_var->value);
		}
		if (env->env_size == 0)
			env->vars[0] = new_var;
		else
		{
			last = *env->vars;
			while (last->next)
				last = last->next;
			last->next = new_var;
			env->env_size++;
		}
		return ;
	}
	free(identifier);
	if (op == 1)
	{
		if (var->value)
			free(var->value);
		var->value = ft_strdup(value);
		var->value_length = ft_strlen(var->value);
		return ;
	}
	if (op == 2)
	{
		new_value = ft_strjoin(var->value, value);;
		if (var->value)
			free(var->value);
		var->value = new_value;
		var->value_length = ft_strlen(var->value);
		return ;
	}
}
