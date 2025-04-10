
#include "minishell.h"
#include <string.h> // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

t_env_var	*get_var(t_env_manager *env, const char *name)
{
	size_t		i;
	t_env_var	*var;

	i = -1;
	var = *env->vars;
	while (++i < env->env_size && var->next)
	{
		if (ft_strcmp((char *)name, var->name) == 0)
			// !!!!!!!!!!!!!!!!!!!!!!!!!! //
			return (var);
		var = var->next;
	}
	return (NULL);
}

static char	*_get_name(t_env_var *var, char *env_var);
static char	*_get_value(t_env_var *var, char *env_var);
static void	_init_manager(char **envp, t_env_manager *env);

t_env_var	**create_env(char **envp, t_env_manager *env)
{
	size_t		i;
	t_env_var	*elt;
	t_env_var	*prev;

	_init_manager(envp, env);
	i = -1;
	if (env->vars == NULL)
		return (NULL);
	env->vars[0] = NULL;
	prev = NULL;
	while (++i < env->env_size)
	{
		elt = malloc(sizeof(t_env_var));
		if (elt == NULL)
			return (NULL); //
		elt->name = _get_name(elt, envp[i]);
		elt->value = _get_value(elt, envp[i]);
		elt->next = NULL;
		if (env->vars[0] == NULL)
			env->vars[0] = elt;
		if (prev)
			prev->next = elt;
		prev = elt;
	}
	return (env->vars);
}

static char	*_get_name(t_env_var *var, char *env_var)
{
	size_t	len;
	char	*res;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
		len++;
	var->name_length = len;
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, env_var, len + 1);
	return (res);
}

static char	*_get_value(t_env_var *var, char *env_var)
{
	size_t	len;
	char	*res;

	while (*env_var && *env_var != '=')
		env_var++;
	var->value_length = 0;
	if (!*env_var)
		return (NULL);
	env_var++;
	len = 0;
	while (env_var[len])
		len++;
	var->value_length = len;
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
	env->vars = malloc(sizeof(t_env_var *));
}
