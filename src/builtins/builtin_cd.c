/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:11 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/13 11:05:52 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exit	_set_home(t_excmd *c);
static void		_update_vars(t_env_manager *env);

t_exit	builtin_cd(t_excmd *c)
{
	if (c->argc > 2)
	{
		puterr(ft_sprintf(": %s: too many arguments\n", c->name), false);
		return (EXIT_FAILURE);
	}
	if (c->argc == 1 && _set_home(c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (c->argc == 2 && chdir(c->argv[1]) == -1)
	{
		puterr(ft_sprintf(": %s: %s No such a file or directory\n",
				c->name, c->argv[1]), false);
		return (EXIT_FAILURE);
	}
	_update_vars(c->env);
	return (EXIT_SUCCESS);
}

static void	_update_vars(t_env_manager *env)
{
	t_env_var	*pwd;
	t_env_var	*old_pwd;
	char		*cwd;

	pwd = get_var(env, "PWD");
	old_pwd = get_var(env, "OLDPWD");
	if (old_pwd)
	{
		if (old_pwd->value)
			free(old_pwd->value);
		if (pwd && pwd->value)
			old_pwd->value = pwd->value;
		else
			old_pwd->value = ft_strdup(""); //
		old_pwd->value_length = ft_strlen(old_pwd->value);
	}
	if (pwd)
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
			pwd->value = cwd;
		else
			pwd->value = ft_strdup(""); //
		pwd->value_length = ft_strlen(pwd->value);
	}
}

static t_exit	_set_home(t_excmd *c)
{
	t_env_var	*home;

	home = get_var(c->env, "HOME");
	if (!home || !home->value)
	{
		puterr(ft_sprintf(": %s: Home variable not set\n", c->name), false);
		return (EXIT_FAILURE);
	}
	if (chdir(home->value) == -1)
	{
		puterr(ft_sprintf(": %s", c->name), true);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
