/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:29 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/19 11:04:37 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	elt = NULL;
	init_all_vars(env, envp, elt, i);
	if (!var_exists(env, "PWD"))
		init_var(env, "PWD");
	if (!var_exists(env, "OLDPWD"))
		init_var(env, "OLDPWD");
	if (!var_exists(env, "SHLVL"))
		init_var(env, "SHLVL");
	ensure_var(env, "PWD", getcwd(NULL, 0));
	ensure_var(env, "SHLVL", ft_strdup("1"));
	_increment_shlevel(env);
	return (env->vars);
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
