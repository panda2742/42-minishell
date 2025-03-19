#include "minishell.h"

t_exit	builtins_env(t_command *c)
{
	char	**env;

	env = env_str(c->env);
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
