#include "minishell.h"

void	show_prompt(void)
{
	const char	*cwd = getcwd(NULL, 0);

	printf(GREEN "%s/ " RESET, ft_strrchr(cwd, '/') + 1);
	free((char *)cwd);
	printf(BLUE "minishell $" RESET);
}
