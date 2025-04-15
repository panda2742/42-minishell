#include "minishell.h"

static void		_load_exec_params(t_minishell *minishell, t_execparams *params,
				t_excmd **cmds);
static t_bool	_create_child(t_excmd *cmd, t_execparams *params);

t_exit	exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_excmd			*cmd;
	t_execparams	params;

	_load_exec_params(minishell, &params, cmds);
	cmd = *cmds;
	while (cmd)
	{
		cmd->envp = minishell->env.envlst;
		if (exec_init_cmd(cmd, &params) == false)
		{
			cmd = cmd->next;
			continue ;
		}
		params.nb_launched++;
		if (_create_child(cmd, &params) == false)
		{
			cmd = cmd->next;
			continue ;
		}
		if (create_streams(cmd) == false)
			exit(0);
		if (cmd->proto == NULL)
			execute_from_path(minishell, cmd, cmds);
		(*cmd->proto)(cmd);

		free_env(cmd->env);
		ft_free_strtab(cmd->envp);
		free_cmds(cmds);
		cmd = cmd->next;
	}
	while (params.nb_launched)
	{
		waitpid(-1, NULL, 0);
		params.nb_launched--;
	}
	ft_free_strtab(minishell->env.envlst);
	return (minishell->last_status);
}


static void	_load_exec_params(t_minishell *minishell, t_execparams *params,
				t_excmd **cmds)
{
	t_excmd	*cmd;
	size_t	i;

	minishell->last_status = EXIT_SUCCESS;
	minishell->env.envlst = env_to_strlst(&minishell->env);
	params->nb_cmd = 0;
	params->nb_launched = 0;
	params->cmds = cmds;
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
			cmd = cmd->next;
			return (false);
		}
	}
	return (true);
}
