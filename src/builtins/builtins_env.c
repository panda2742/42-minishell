#include "minishell.h"

t_exit	builtins_env(t_command *c)
{
	size_t	i;
	t_env	*var;

	i = -1;
	var = *c->env->vars;
	while (++i < c->env->env_size)
	{
		if (ft_printf("%s%s%s=%s\n", BLUE, var->name, RESET, var->value) == -1)
		{
			c->status = EXIT_FAILURE;
			break ;
		}
		var = var->next;
	}
	return (c->status);
}
