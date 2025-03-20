#include "minishell.h"

void	*handle_env_mem_alloc(t_env_manager *env)
{
	free_env(env);
	return (NULL);
}
