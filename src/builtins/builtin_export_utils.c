/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:37:18 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/19 11:35:20 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_do_op(t_env_manager *env, char *str)
{
	char			*identifier;
	unsigned char	op;
	char			*value;
	t_env_var		*var;

	identifier = get_identifier(str);
	if (valid_identifier_name(identifier) == false)
	{
		puterr(ft_sprintf(": export: `%s': not a valid identifier\n",
				str), false);
		return (free(identifier));
	}
	op = get_operation(str);
	if (op == 3)
		puterr(ft_sprintf(": export: `%s': not a valid identifier\n",
				str), false);
	if (op == 3)
		return (free(identifier));
	value = get_value(str);
	var = get_var(env, identifier);
	if (var == NULL)
		return (_existing_var_op(env, identifier, op, value));
	free(identifier);
	_non_existing_var_op(op, var, value);
}

void	_existing_var_op(t_env_manager *env, char *identifier,
	unsigned char op, char *value)
{
	t_env_var		*last;
	t_env_var		*new_var;

	new_var = _create_new_var(identifier, op, value);
	if (new_var == NULL)
		return ;
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
	env->env_size++;
	return ;
}

t_env_var	*_create_new_var(char *identifier, unsigned char op,
				char *value)
{
	t_env_var		*new_var;

	new_var = ft_memalloc(sizeof(t_env_var));
	if (new_var == NULL)
	{
		free(identifier);
		puterr(ft_strdup(": Memory allocation error\n"), false);
		return (NULL);
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
	return (new_var);
}

void	_non_existing_var_op(unsigned char op, t_env_var *var, char *value)
{
	char			*new_value;

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
		new_value = ft_strjoin(var->value, value);
		if (var->value)
			free(var->value);
		var->value = new_value;
		var->value_length = ft_strlen(var->value);
		return ;
	}
}
