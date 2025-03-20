#include "minishell.h"

void	debug_display_env(t_env_manager *env)
{
	printf(GREEN "\n[ Environment ]\n" RESET);
	printf(BLUE "\n  Address:       " RESET);
	printf("%p\n", env);
	printf(YELLOW "  Size:          " RESET);
	printf("%zu [%p]\n", env->env_size, &env->env_size);
	printf(MAGENTA "  Variables:     " RESET);
	printf("%p\n", env->vars);
	printf(RED "  First element: " RESET);
	printf("%s=%s ", (*env->vars)->name, (*env->vars)->value);
	printf("[%p]\n\n", *env->vars);
	printf(GREEN "---------------\n\n" RESET);
}

t_env	*get_var(t_env_manager *env, const char *name)
{
	size_t	i;
	t_env	*var;

	i = -1;
	var = *env->vars;
	while (++i < env->env_size && var->next)
	{
		if (ft_strncmp(name, var->name, ft_strlen(var->name)) == 0)
			return (var);
		var = var->next;
	}
	return (NULL);
}
