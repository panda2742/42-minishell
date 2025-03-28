#include "minishell.h"

void	*handle_env_mem_alloc(t_env_manager *env)
{
	free_env(env);
	return (NULL);
}

t_exit	command_failure(t_excmd *c, char *message, t_bool call_perror)
{
	puterr(message, call_perror);
	c->status = EXIT_FAILURE;
	return (c->status);
}
