#include "minishell.h"

t_exit	builtins_export(t_excmd *c)
{
	printf(MAGENTA "<'export' builtin to code>\n" RESET);
	(void)c;
	return (0);
}
