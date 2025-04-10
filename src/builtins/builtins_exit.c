#include "minishell.h"

t_exit	builtins_exit(t_excmd *c)
{
	(void)c;
	free_env(c->env);
	ft_free_strtab(c->argv);
	exit(c->status);
}
