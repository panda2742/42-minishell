#include "minishell.h"

t_exit	builtins_echo(t_command *c)
{
	printf(MAGENTA "<'echo' builtin to code>\n" RESET);
	(void)c;
	return (0);
}
