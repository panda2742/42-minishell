#include "minishell.h"

static char	*_set_home(t_env_manager *env);
static void	_update_vars(t_env *pwd, t_env *old_pwd);

t_exit	builtins_cd(t_command *c)
{
	t_env	*pwd;
	t_env	*old_pwd;

	if (c->argc >= 2)
	{
		puterr(E_BUILTINS_CD_WARGS, false, NULL);
		c->status = EXIT_FAILURE;
		return (c->status);
	}
	if (c->argc == 0 && !_set_home(c->env))
	{
		c->status = EXIT_FAILURE;
		return (c->status);
	}
	else if (c->argc > 0 && chdir(c->args[0]) == -1)
	{
		puterr(0, true, c->args[0]);
		c->status = EXIT_FAILURE;
		return (c->status);
	}
	pwd = get_var(c->env, "PWD");
	old_pwd = get_var(c->env, "OLDPWD");
	_update_vars(pwd, old_pwd);
	return (c->status);
}

static void	_update_vars(t_env *pwd, t_env *old_pwd)
{
	char	*cwd;

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

static char	*_set_home(t_env_manager *env)
{
	t_env	*home;

	home = get_var(env, "HOME");
	if (!home || !home->value)
	{
		puterr(E_BUILTINS_CD_NOHOME, false, NULL);
		return (NULL);
	}
	if (chdir(home->value) == -1)
	{
		puterr(0, true, NULL);
		return (NULL);
	}
	return (home->value);
}
