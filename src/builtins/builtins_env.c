#include "minishell.h"

t_exit	builtins_env(t_command *c)
{
	while (*c->env)
	{
		printf("%s\n", *c->env);
		c->env++;
	}
	return (0);
}
