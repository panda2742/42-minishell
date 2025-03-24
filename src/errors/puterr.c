#include "minishell.h"

void	puterr(t_error err)
{
	const char	*errmsg = error_msgs()[err];

	ft_putstr_fd(RED PROJECT_NAME ": ", 2);
	ft_putstr_fd((char *)errmsg, 2);
	ft_putstr_fd("\n" RESET, 2);
}
