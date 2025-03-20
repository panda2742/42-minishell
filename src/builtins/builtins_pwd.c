#include "minishell.h"

t_exit	builtins_pwd(t_command	*c)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		c->status = EXIT_FAILURE;
		return (c->status);
	}
	if (ft_putstr_fd(buffer, 1) == -1)
	{
		free(buffer);
		c->status = EXIT_FAILURE;
		return (c->status);
	}
	free(buffer);
	if (ft_putstr_fd("\n", 1) == -1)
		c->status = EXIT_FAILURE;
	return (c->status);
}
