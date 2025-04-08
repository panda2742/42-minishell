#include "minishell.h"

t_exit	heredoc(char *buffer, char *del, t_bool skip_writing)
{
	char	*line;

	(void)del;
	while (1)
	{
		line = readline("> ");
		if (buffer && !skip_writing)
			buffer = line;
		break ;
	}
	return (EXIT_SUCCESS);
}
