/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:07:18 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/07 11:25:45 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdproto	load_builtin(const char *command_name, t_cmdproto *proto)
{
	static char			*builtins[7] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"
	};
	static t_cmdproto	command_prototypes[7] = {
		builtin_cd, builtin_echo, builtin_env, builtin_exit,
		builtin_export, builtin_pwd, builtin_unset
	};
	int					i;

	i = -1;
	*proto = NULL;
	while (++i < 7)
	{
		if (ft_strcmp((char *)command_name, builtins[i]) == 0)
		{
			*proto = command_prototypes[i];
			break ;
		}
	}
	return (*proto);
}

char	*get_full_path(char *path, char *cmd_name)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp2, cmd_name);
	free(tmp2);
	return (tmp);
}

int	close_pipe(t_excmd *cmd, int streams)
{
	int	res;

	if (cmd == NULL)
		return (0);
	res = 0;
	if (streams & 1 && cmd->pipe_open[0])
	{
		res |= close(cmd->pipe[0]);
		cmd->pipe_open[0] = false;
	}
	if ((streams >> 1) & 1 && cmd->pipe_open[1])
	{
		res |= close(cmd->pipe[1]);
		cmd->pipe_open[1] = false;
	}
	return (res);
}
