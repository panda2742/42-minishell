#include "minishell.h"

void	puterr(t_error err, t_bool call_perror, char *err_arg)
{
	const char	*errmsg = error_msgs()[err];

	ft_putstr_fd(RED PROJECT_NAME ": cd", 2);
	if (call_perror)
	{
		if (err_arg)
			ft_putstr_fd(": ", 2);
		perror(err_arg);
	}
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd((char *)errmsg, 2);
		ft_putstr_fd("\n" RESET, 2);
	}
}
