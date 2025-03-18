#include "minishell.h"

t_exit	builtins_cd(t_command *c)
{
	printf(MAGENTA "<'cd' builtin to code>\n" RESET);
	(void)c;
	return (0);
}
