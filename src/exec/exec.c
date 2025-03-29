#include "minishell.h"

t_exit	exec_command(t_minishell *minishell, t_excmd **cmds)
{
	t_exit		status;
	t_cmdproto	*proto;
	t_excmd		*cmd;

	status = EXIT_SUCCESS;
	proto = NULL;

	(void)minishell;
	// here docs
	cmd = *cmds;
	while (cmd)
	{
		if (cmd->has_heredoc)
			heredoc(cmd->heredoc_del, cmd->heredoc_content);
	}

	// exec
	cmd = *cmds;
	while (cmd)
	{
		
		if (cmd->is_builtin)
		{
			if (!cmd->in_a_child)
			{
				(*cmd->proto)(cmd);
				status = cmd->status;
			}
			cmd = cmd->next;
			continue ;
		}
	}
	return (status);
}

t_cmdproto	*load_builtin(const char *command_name, t_cmdproto *proto)
{
	static char			*builtins[7] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"
	};
	static t_cmdproto	command_prototypes[7] = {
		builtins_cd, builtins_echo, builtins_env, builtins_exit,
		builtins_export, builtins_pwd, builtins_unset
	};
	size_t				len;
	int					i;

	i = -1;
	while (++i < 7)
	{
		len = ft_strlen(builtins[i]);
		if (ft_strncmp(command_name, builtins[i], len) == 0)
		{
			proto = &command_prototypes[i];
			break ;
		}
	}
	return (proto);
}
