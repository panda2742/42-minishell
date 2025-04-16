/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:07:18 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/16 10:56:24 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int sfd, t_bool *door)
{
	if (sfd == 0 || sfd == 1)
		return ;
	close(sfd);
	if (door)
		*door = false;
}

t_cmdproto	load_builtin(const char *command_name, t_cmdproto *proto)
{
	static char			*builtins[7] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"
	};
	static t_cmdproto	command_prototypes[7] = {
		builtin_cd, builtin_echo, builtin_env, builtin_exit,
		builtin_export, builtin_pwd, builtin_unset
	};
	size_t				len;
	int					i;

	i = -1;
	*proto = NULL;
	while (++i < 7)
	{
		len = ft_strlen(builtins[i]);
		if (ft_strncmp(command_name, builtins[i], len) == 0)
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
	return (tmp);
}
