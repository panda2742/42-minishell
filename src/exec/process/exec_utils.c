/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:07:18 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 15:44:23 by ehosta           ###   ########.fr       */
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

t_bool	load_env_strlst(t_execvars *vars)
{
	t_excmd	*cmd;

	vars->minishell->env.envlst = env_to_strlst(&vars->minishell->env);
	if (vars->minishell->env.envlst == NULL)
	{
		vars->errs.exc_env_strlst = 1;
		free(vars->cmds);
		puterr(ft_sprintf(
				": error: Pipeline init failure (memory allocation),\
					killing %s\n" PROJECT_NAME), false);
		return (false);
	}
	cmd = *vars->cmds;
	while (cmd)
	{
		cmd->envp = vars->minishell->env.envlst;
		cmd = cmd->next;
	}
	return (true);
}

void	print_core_dumped_and_st(t_execvars *vars)
{
	write(1, "Quit (core dumped)", 19);
	vars->status = 128 + SIGQUIT;
}
