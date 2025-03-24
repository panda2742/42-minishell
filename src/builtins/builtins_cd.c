#include "minishell.h"

t_exit	builtins_cd(t_command *c)
{
	t_env	*pwd;
	t_env	*oldpwd;

	if (c->argc >= 2)
	{
		puterr(E_BUILTINS_CD_WARGS);
		c->status = EXIT_FAILURE;
		return (c->status);
	}
	pwd = get_var(c->env, "PWD");
	oldpwd = get_var(c->env, "OLDPWD");
	if (oldpwd)
	{
		if (pwd)
		{
			if (oldpwd->value)
				free(oldpwd->value);
			if (pwd->value)
				oldpwd->value = pwd->value;
			else
				oldpwd->value = NULL;
		}
	}
	if (pwd)
	{
		if (c->args[0])
		{
			printf("%s\n", c->args[0]);
			chdir(c->args[0]);
		}
	}
	return (c->status);
}
