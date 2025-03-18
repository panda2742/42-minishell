#include "minishell.h"

t_exit	builtins_exit(t_command *c)
{
	(void)c;
	ft_free_strtab(c->env);
	exit(EXIT_SUCCESS);
}
