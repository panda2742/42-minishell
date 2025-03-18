#include "minishell.h"

t_exit	builtins_unset(t_command *c)
{
	printf(MAGENTA "<'unset' builtin to code>\n" RESET);
	(void)c;
	return (0);
}
