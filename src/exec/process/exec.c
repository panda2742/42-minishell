/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:57:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/18 16:41:30 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		*_load_exec_params(t_minishell *minishell, t_execparams *params,
					t_excmd **cmds);
static t_bool	_create_child(t_excmd *cmd, t_execparams *params);

t_execparams	exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_excmd			*cmd;
	t_execparams	params;
	t_streamfd		std_dup[2];

	if (_load_exec_params(minishell, &params, cmds) == NULL)
	{
		free_cmds(cmds);
		puterr(ft_sprintf(
			": error: Pipeline init failure (memory allocation), skipping\n"
			), false);
		params.status = EXIT_FAILURE;
		params.error_occured = true;
		params.prompt_back = false;
		return (params);
	}
	cmd = *cmds;
	while (cmd)
	{
		if (cmd->prev && cmd->prev->argc > 0)
			cmd->$_ = ft_strdup(cmd->prev->argv[cmd->prev->argc - 1]);
		cmd->envp = minishell->env.envlst;
		if (exec_init_cmd(cmd, &params) == false)
		{
			if (cmd->next && cmd->pipe_open[0] == false)
			{
				free_cmds(cmds);
				puterr(ft_sprintf(
					": error: Pipe creation failure"
					), true);
				params.error_occured = true;
				params.status = EXIT_FAILURE;
				params.prompt_back = true;
				break ;
			}
			cmd = cmd->next;
			continue ;
		}
		params.nb_launched++;
		if (_create_child(cmd, &params) == false)
		{
			cmd = cmd->next;
			continue ;
		}
		if (create_streams(cmd, &std_dup[0], &std_dup[1]) == false)
			exit(0);
		if (cmd->proto == NULL)
			execute_from_path(minishell, cmd);
		else
		{
			(*cmd->proto)(cmd);
			if (cmd->in_a_child)
			{
				if (std_dup[0].type == STREAM_STD)
					close(std_dup[0].fd);
				if (std_dup[1].type == STREAM_STD)
					close(std_dup[1].fd);
				exit(0);
			}
			else
			{
				if (std_dup[0].type == STREAM_STD && dup2(std_dup[0].fd, STDIN_FILENO) == -1)
				{
					puterr(ft_sprintf(": dup2 in-stream error"), true);
					if (std_dup[1].type == STREAM_STD && dup2(std_dup[1].fd, STDOUT_FILENO) == -1)
					{
						puterr(ft_sprintf(": dup2 out-stream error"), true);
						close(std_dup[1].fd);
					}
					close(std_dup[0].fd);
					return (params);
				}
				if (std_dup[1].type == STREAM_STD && dup2(std_dup[1].fd, STDOUT_FILENO) == -1)
				{
					puterr(ft_sprintf(": dup2 out-stream error"), true);
					close(std_dup[1].fd);
				}
			}
		}
		if (cmd->in_a_child && cmd->proto == NULL)
		{
			free_env(cmd->env);
			ft_free_strtab(cmd->envp);
			free_cmds(cmds);
			exit(0);
		}
		cmd = cmd->next;
	}
	cmd = *cmds;
	while (params.nb_launched)
	{
		if (cmd->prev)
			waitpid(-1, NULL, 0);
		else
			waitpid(-1, &minishell->last_status, 0);
		params.nb_launched--;
		cmd = cmd->next;
	}
	ft_free_strtab(minishell->env.envlst);
	return (params);
}

static void	*_load_exec_params(t_minishell *minishell, t_execparams *params,
				t_excmd **cmds)
{
	t_excmd	*cmd;
	size_t	i;

	minishell->env.envlst = env_to_strlst(&minishell->env);
	if (minishell->env.envlst == NULL)
		return (NULL);
	minishell->last_status = EXIT_SUCCESS;
	params->nb_cmd = 0;
	params->nb_launched = 0;
	params->cmds = cmds;
	params->error_occured = false;
	params->status = EXIT_SUCCESS;
	params->prompt_back = true;
	cmd = *cmds;
	i = 0;
	while (cmd)
	{
		params->nb_cmd++;
		cmd->id = i;
		cmd->proto = load_builtin(cmd->name, &cmd->proto);
		i++;
		cmd = cmd->next;
	}
	return ((void *)0x1);
}

static t_bool	_create_child(t_excmd *cmd, t_execparams *params)
{
	int	forkid;

	if (cmd->in_a_child)
	{
		forkid = fork();
		if (forkid > 0 || forkid < 0)
		{
			if (forkid == -1)
			{
				params->nb_launched--;
				puterr(ft_sprintf(": fork error"), true);
			}
			close_pipe(cmd->pipe[1], &cmd->pipe_open[1]);
			return (false);
		}
	}
	return (true);
}
