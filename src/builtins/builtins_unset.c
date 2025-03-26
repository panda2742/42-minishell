#include "minishell.h"

t_exit	builtins_unset(t_command *c)
{
	t_env	*var;
	t_env	*prev;

	if (c->argc > 2)
		return (command_failure(c, ft_sprintf(": %s: Too many arguments\n", c->name), false));
	if (c->argc == 1)
		return (command_failure(c, ft_sprintf(": %s: Too few arguments\n", c->name), false));
	var = *c->env->vars;
	prev = NULL;
	while (var)
	{
		if (ft_strncmp(var->name, c->args[1], ft_strlen(var->name)) == 0)
		{
			if (!prev)
				c->env->vars[0] = var->next;
			else
				prev->next = var->next;
			free(var->value);
			free(var);
			break ;
		}
		prev = var;
		if (var->next)
			var = var->next;
	}
	return (0);
}
