
#include "minishell.h"

int	ft_cmd_lstsize(t_word *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}