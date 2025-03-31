#include "minishell.h"

t_exit	heredoc(char *buffer, char *del)
{
	(void)del;
	buffer = "Ceci est un test";
	return (EXIT_SUCCESS);
}
