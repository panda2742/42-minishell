#include "minishell.h"

void	free_env(t_env_manager *env)
{
	size_t	i;
	t_env	*var;
	t_env	*next;

	i = -1;
	var = *env->vars;
	while (++i < env->env_size && var->next)
	{
		next = var->next;
		free(var->name);
		free(var->value);
		free(var);
		var = next;
	}
	free(var->name);
	free(var->value);
	free(var);
	free(env->vars);
}
