#include "minishell.h"

static char	*_get_name(char *env_var);
static char	*_get_value(char *env_var);
static void	_init_manager(char **envp, t_env_manager *env);

t_env	**create_env(char **envp, t_env_manager *env)
{
	size_t	i;
	t_env	*elt;
	t_env	*prev;

	_init_manager(envp, env);
	i = -1;
	if (env->vars == NULL)
		return (NULL);
	env->vars[0] = NULL;
	prev = NULL;
	while (++i < env->env_size)
	{
		elt = malloc(sizeof(t_env));
		if (elt == NULL)
			return (handle_env_mem_alloc(env));
		elt->name = _get_name(envp[i]);
		elt->value = _get_value(envp[i]);
		elt->next = NULL;
		if (env->vars[0] == NULL)
			env->vars[0] = elt;
		if (prev)
			prev->next = elt;
		prev = elt;
	}
	return (env->vars);
}

static char	*_get_name(char *env_var)
{
	size_t	len;
	char	*res;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, env_var, len + 1);
	return (res);
}

static char	*_get_value(char *env_var)
{
	size_t	len;
	char	*res;

	while (*env_var && *env_var != '=')
		env_var++;
	if (!*env_var)
		return (NULL);
	env_var++;
	len = 0;
	while (env_var[len])
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, env_var, len + 1);
	return (res);
}

static void	_init_manager(char **envp, t_env_manager *env)
{
	env->env_size = 0;
	while (envp[env->env_size])
		env->env_size += 1;
	env->vars = malloc(sizeof(t_env *));
}
