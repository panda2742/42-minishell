/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:53:45 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 14:51:02 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_var	**_fill_vars(t_env_var **res, t_env_manager *env);

t_env_var	**dup_env_vars(t_env_manager *env)
{
	t_env_var	**res;

	res = ft_memalloc(sizeof(t_env_var *));
	if (res == NULL)
		return (NULL);
	if (env->env_size == 0)
	{
		free(res);
		return (NULL);
	}
	res[0] = NULL;
	return (_fill_vars(res, env));
}

static void	_set_elt(t_env_var *elt, t_env_var *mirror)
{
	elt->name = mirror->name;
	elt->name_length = mirror->name_length;
	elt->value = mirror->value;
	elt->value_length = mirror->value_length;
	elt->next = NULL;
}

static t_env_var	**_fill_vars(t_env_var **res, t_env_manager *env)
{
	size_t		i;
	t_env_var	*mirror;
	t_env_var	*elt;
	t_env_var	*prev;

	i = -1;
	mirror = *env->vars;
	prev = NULL;
	while (++i < env->env_size)
	{
		elt = ft_memalloc(sizeof(t_env_var));
		if (elt == NULL)
			return (res);
		_set_elt(elt, mirror);
		if (!res[0])
			res[0] = elt;
		if (prev)
			prev->next = elt;
		prev = elt;
		mirror = mirror->next;
	}
	return (res);
}

void	free_dup_vars(t_env_var **vars)
{
	size_t		i;
	t_env_var	*elt;
	t_env_var	*tmp;

	i = -1;
	if (!vars)
		return ;
	elt = *vars;
	while (elt)
	{
		tmp = elt->next;
		free(elt);
		elt = tmp;
	}
	free(vars);
}
