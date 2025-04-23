#include "minishell.h"

static t_bool	_restore_in_dup(t_streamfd *sfd, int default_fd);

t_bool	restore_std(t_streamfd *in_dup, t_streamfd *out_dup)
{
	t_bool	restore_res[2];

	restore_res[0] = true;
	restore_res[1] = true;
	if (in_dup->fd != -1)
		restore_res[0] = _restore_in_dup(in_dup, STDIN_FILENO);
	if (out_dup->fd != -1)
		restore_res[1] = _restore_in_dup(out_dup, STDOUT_FILENO);
	if (in_dup->fd != -1)
		sclose_fd(in_dup->fd, NULL);
	if (out_dup->fd != -1)
		sclose_fd(out_dup->fd, NULL);
	return (restore_res[0] & restore_res[1]);
}

static t_bool	_restore_in_dup(t_streamfd *sfd, int default_fd)
{
	int	res;

	res = dup2(sfd->fd, default_fd);
	if (res == -1)
	{
		if (default_fd == STDIN_FILENO)
			puterr(ft_sprintf(": failed restoring standard input"), true);
		else
			puterr(ft_sprintf(": failed restoring standard output"), true);
		return (false);
	}
	return (true);
}
