#include "minishell.h"

t_exit	builtins_cd(t_command *c)
{
	t_env	*pwd;
	t_env	*oldpwd;

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
		
	}
	return (0);
}
