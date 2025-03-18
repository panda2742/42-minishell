#include "minishell.h"

t_exit	builtins_export(t_command *c)
{
	printf(MAGENTA "<'export' builtin to code>\n" RESET);
	(void)c;
	return (0);
}
