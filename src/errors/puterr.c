#include "minishell.h"

void	puterr(char *message, t_bool call_perror)
{
	ft_putstr_fd(RED PROJECT_NAME, 2);
	if (message)
	{
		if (call_perror)
			perror(message);
		else
			ft_putstr_fd(message, 2);
		free(message);
	}
	else
	{
		if (call_perror)
			perror(": An error occured");
		else
			ft_putstr_fd(": An error occured\n", 2);
	}
	ft_putstr_fd(RESET, 2);
}
