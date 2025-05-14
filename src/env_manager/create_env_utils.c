/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:41:43 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 14:59:00 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*_get_name(t_env_var *var, char *env_var);
static char			*_get_value(t_env_var *var, char *env_var);

static void	_free_null(t_env_manager *env)
{
	free_env(env);
	return ;
}

void	init_all_vars(t_env_manager *env, char **envp, t_env_var *elt, size_t i)
{
	t_env_var	*prev;

	prev = NULL;
	while (++i < env->env_size)
	{
		elt = ft_memalloc(sizeof(t_env_var));
		if (elt == NULL)
			return (_free_null(env));
		elt->name = _get_name(elt, envp[i]);
		if (elt->name == NULL)
		{
			free(elt);
			return (_free_null(env));
		}
		elt->value = _get_value(elt, envp[i]);
		elt->next = NULL;
		if (!env->vars[0])
			env->vars[0] = elt;
		if (prev)
			prev->next = elt;
		prev = elt;
	}
}

static char	*_get_name(t_env_var *var, char *env_var)
{
	size_t	len;
	char	*res;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
		len++;
	var->name_length = len;
	res = ft_memalloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, env_var, len + 1);
	return (res);
}

static char	*_get_value(t_env_var *var, char *env_var)
{
	size_t	len;
	char	*res;

	while (*env_var && *env_var != '=')
		env_var++;
	var->value_length = 0;
	if (!*env_var)
		return (NULL);
	env_var++;
	len = 0;
	while (env_var[len])
		len++;
	var->value_length = len;
	res = ft_memalloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, env_var, len + 1);
	return (res);
}
