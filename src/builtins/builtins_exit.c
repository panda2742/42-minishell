#include "minishell.h"

t_exit	builtins_exit(t_command *c)
{
	(void)c;
	free_env(c->env);
	ft_free_strtab(c->args);
	exit(c->status);
}
