#include "minishell.h"

static command_prototype	*_is_builtin(const char *command_name);

t_exit	exec_command(t_minishell *minishell, const char *command_name, const char **command_args)
{
	command_prototype	*proto_res;
	command_prototype	prototype;
	t_command			command;

	command.name = (char *)command_name;
	command.args = (char **)command_args;
	command.env = minishell->env;
	proto_res = _is_builtin(command.name);
	if (!proto_res)
		return (1);
	prototype = *proto_res;
	prototype(&command);
	return (0);
}

static command_prototype	*_is_builtin(const char *command_name)
{
	static char	*builtins[7] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"
	};
	static command_prototype command_prototypes[7] = {
		builtins_cd, builtins_echo, builtins_env, builtins_exit, builtins_export, builtins_pwd, builtins_unset
	};
	size_t		len;
	int			i;

	i = -1;
	while (++i < 7)
	{
		len = ft_strlen(builtins[i]);
		if (ft_strncmp(command_name, builtins[i], len) == 0)
			return (&command_prototypes[i]);
	}
	return (NULL);
}
