#include "minishell.h"

static t_exit	_set_home(t_excmd *c);
static void		_update_vars(t_env_manager *env);

t_exit	builtins_cd(t_excmd *c)
{
	if (c->argc > 2)
		return (
			command_failure(
				c, ft_sprintf(": %s: Too many arguments\n", c->name), false
			)
		);
	if (c->argc == 1 && _set_home(c) == EXIT_FAILURE)
		return (c->status);
	else if (c->argc == 2 && chdir(c->argv[1]) == -1)
		return (
			command_failure(
				c, ft_sprintf(": %s: %s", c->name, c->argv[1]), true
			)
		);
	_update_vars(c->env);
	return (c->status);
}

static void	_update_vars(t_env_manager *env)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*cwd;

	pwd = get_var(env, "PWD");
	old_pwd = get_var(env, "OLDPWD");
	if (old_pwd)
	{
		if (old_pwd->value)
			free(old_pwd->value);
		if (pwd && pwd->value)
			old_pwd->value = pwd->value;
		else
			old_pwd->value = NULL;
	}
	if (pwd)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return ;
		pwd->value = cwd;
	}
}

static t_exit	_set_home(t_excmd *c)
{
	t_env	*home;

	home = get_var(c->env, "HOME");
	if (!home || !home->value)
		return (
			command_failure(
				c, ft_sprintf(": %s: Home variable not set\n", c->name), false
			)
		);
	if (chdir(home->value) == -1)
		return (command_failure(c, ft_sprintf(": %s", c->name), true));
	return (c->status);
}
