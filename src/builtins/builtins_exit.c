#include "minishell.h"

t_exit	builtins_exit(t_command *c)
{
	(void)c;
	free_env(c->env);
	exit(c->status);
}
