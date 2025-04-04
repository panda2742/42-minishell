#include "minishell.h"

void	free_cmds(t_excmd **cmds)
{
	t_excmd	*cmd;
	t_excmd	*tmp;

	cmd = *cmds;
	while (cmd)
	{
		free(cmd->name);
		free(cmd->raw);
		ft_free_strtab(cmd->argv);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	free(cmds);
}
