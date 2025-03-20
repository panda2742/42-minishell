#include "minishell.h"

static t_cmdproto	*_is_builtin(const char *command_name);

t_exit	exec_command(
			t_minishell *minishell,
			const char *command_name,
			const char **command_args
			)
{
	t_cmdproto	*proto_res;
	t_cmdproto	prototype;
	t_command	command;

	command.name = (char *)command_name;
	command.args = (char **)command_args;
	command.env = &minishell->env;
	command.status = EXIT_SUCCESS;
	proto_res = _is_builtin(command.name);
	if (!proto_res)
		return (1);
	prototype = *proto_res;
	prototype(&command);
	return (0);
}

static t_cmdproto	*_is_builtin(const char *command_name)
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
			return (&command_prototypes[i]);
	}
	return (NULL);
}
