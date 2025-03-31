#include "minishell.h"

t_env_var	*get_var(t_env_manager *env, const char *name)
{
	size_t	i;
	t_env_var	*var;

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

void	nb_by_name(t_env_manager *env, const char *section, size_t *ressize)
{
	size_t		i;
	size_t		len;
	t_env_var	*var;
	char		*res;

	i = -1;
	len = 0;
	var = *env->vars;
	while (++i < env->env_size && var)
	{
		res = ft_strnstr(var->name, section, var->name_length);
		if (res)
			len++;
		var = var->next;
	}
	*ressize = len;
}
