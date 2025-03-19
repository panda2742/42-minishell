#include "minishell.h"

static char	*_get_name(const char *env_var);
static char	*_get_value(const char *env_var);

t_env	**create_env(const char **envp, t_env_manager *env)
{
	size_t	i;
	t_env	*elt;
	t_env	*prev;

	env->env_size = 0;
	while (envp[env->env_size])
		env->env_size += 1;
	i = -1;
	env->vars = malloc(sizeof(t_env *));
	if (env->vars == NULL)
		return (NULL);
	prev = NULL;
	while (++i < env->env_size)
	{
		elt = malloc(sizeof(t_env));
		if (elt == NULL)
			return (NULL);
		elt->name = _get_name(envp[i]);
		elt->value = _get_value(envp[i]);
		elt->next = NULL;
		if (env->vars == NULL)
			env->vars = &elt;
		if (prev)
			prev->next = elt;
		printf("%p -> %p %s=%s\n", prev, elt, elt->name, elt->value);
		prev = elt;
	}
	return (env->vars);
}

static char	*_get_name(const char *env_var)
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

static char	*_get_value(const char *env_var)
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
