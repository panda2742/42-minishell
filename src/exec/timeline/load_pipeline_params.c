#include "minishell.h"

static t_bool	_load_env_strlst(t_minishell *minishell, t_execparams *params);

t_bool	load_pipeline_params(t_minishell *minishell, t_execparams *params,
	t_excmd **cmds)
{
	t_excmd	*cmd;

	params->nb_cmd = 0;
	params->nb_launched = 0;
	params->cmds = cmds;
	params->status = 0;
	params->errs.errors_raw = 0;
	if (_load_env_strlst(minishell, params) == false)
	{
		free(cmds);
		puterr(ft_sprintf(
			": error: Pipeline init failure (memory allocation), killing %s\n"
			PROJECT_NAME), false);
		return (false);
	}
	cmd = *params->cmds;
	while (cmd)
	{
		params->nb_cmd++;
		cmd->id = params->nb_cmd;
		if (cmd->name)
			cmd->proto = load_builtin(cmd->name, &cmd->proto);
		cmd = cmd->next;
	}
	return (true);
}

static t_bool	_load_env_strlst(t_minishell *minishell, t_execparams *params)
{
	minishell->env.envlst = env_to_strlst(&minishell->env);
	if (minishell->env.envlst == NULL)
	{
		params->errs.exc_env_strlst = 1;
		return (false);
	}
	return (true);
}
