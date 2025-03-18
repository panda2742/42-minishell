#include "minishell.h"

t_exit	builtins_pwd(t_command	*c)
{
	char	*buffer;

	(void)c;
	buffer = getcwd(NULL, 0);
	write(1, buffer, ft_strlen(buffer));
	free(buffer);
	write(1, "\n", 1);
	return (0);
}
