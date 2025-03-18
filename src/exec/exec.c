/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:05:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/18 13:40:27 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_is_builtin(const char *command_name);

t_exit	exec_command(const char *command_name, const char **command_args)
{
	// command_prototype	prototype;
	t_command			command;
	char				*builtin_res;

	command.name = (char *)command_name;
	command.args = (char **)command_args;
	builtin_res = _is_builtin(command.name);
	if (!builtin_res)
		return (1);
	if (ft_strncmp(command.name, "pwd", 3) == 0)
		return (builtins_pwd(&command));
	return (0);
}

static char	*_is_builtin(const char *command_name)
{
	static char	*builtins[1] = {
		"pwd"
	};
	size_t		len;
	int			i;

	i = -1;
	while (++i < 1)
	{
		len = ft_strlen(builtins[i]);
		if (ft_strncmp(command_name, builtins[i], len) == 0)
			return (builtins[i]);
	}
	return (NULL);
}
