/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:29 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/09 12:32:29 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*_get_name(t_env_var *var, char *env_var);
static char			*_get_value(t_env_var *var, char *env_var);
static t_env_var	**_init_manager(char **envp, t_env_manager *env);
static void			_increment_shlevel(t_env_manager *env);

t_env_var	**create_env(char **envp, t_env_manager *env)
{
	size_t		i;
	t_env_var	*elt;
	t_env_var	*prev;

	if (_init_manager(envp, env) == NULL)
		return (NULL);
	i = -1;
	env->vars[0] = NULL;
	prev = NULL;
	while (++i < env->env_size)
	{
		elt = ft_memalloc(sizeof(t_env_var));
		if (elt == NULL)
		{
			free_env(env);
			return (NULL);
		}
		elt->name = _get_name(elt, envp[i]);
		if (elt->name == NULL)
		{
			free(elt);
			free_env(env);
			return (NULL);
		}
		elt->value = _get_value(elt, envp[i]);
		if (elt->value == NULL)
		{
			free(elt->name);
			free(elt);
			free_env(env);
			return (NULL);
		}
		elt->next = NULL;
		if (!env->vars[0])
			env->vars[0] = elt;
		if (prev)
			prev->next = elt;
		prev = elt;
	}
	_increment_shlevel(env);
	return (env->vars);
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

static t_env_var	**_init_manager(char **envp, t_env_manager *env)
{
	env->vars = ft_memalloc(sizeof(t_env_var *));
	if (env->vars == NULL)
		return (NULL);
	env->env_size = 0;
	while (envp[env->env_size])
		env->env_size += 1;
	return (env->vars);
}

static void	_increment_shlevel(t_env_manager *env)
{
	t_env_var	*shlevel_var;
	int64_t		lvl_value;

	shlevel_var = get_var(env, "SHLVL");
	if (shlevel_var == NULL || shlevel_var->value == NULL)
		return ;
	lvl_value = ft_atoll(shlevel_var->value) + 1;
	free(shlevel_var->value);
	shlevel_var->value = ft_lltoa(lvl_value);
	if (shlevel_var->value)
		shlevel_var->value_length = ft_strlen(shlevel_var->value);
}
