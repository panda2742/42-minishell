#include "minishell.h"

static char	*_create_env_str(t_env *env);

char	**env_str(t_env_manager *env)
{
	size_t	i;
	char	**res;
	t_env	*var;

	var = *env->vars;
	res = malloc(sizeof(char *) * (env->env_size + 1));
	if (res == NULL)
		return (NULL);
	ft_printf("caca 0\n");
	i = -1;
	while (++i < env->env_size)
	{
		ft_printf("caca 0.5\n");
		if (!var)
			return (res);
		ft_printf("caca 1\n");
		res[i] = _create_env_str(var);
		if (res[i] == NULL)
		{
			ft_free_strtab(res);
			return (NULL);
		}
		ft_printf("caca 2\n");
		printf("%p\n", var->next);
		var = var->next;
		ft_printf("caca 3\n");
	}
	ft_printf("caca 4\n");
	res[env->env_size] = 0;
	return (res);
}

static char	*_create_env_str(t_env *var)
{
	size_t	name_len;
	size_t	value_len;
	char	*res;

	ft_printf("caca 1 %s\n", var->name);
	name_len = ft_strlen(var->name);
	ft_printf("caca 2\n");
	value_len = ft_strlen(var->value);
	ft_printf("caca 3\n");
	res = malloc(sizeof(char) * (name_len + value_len + 1));
	if (res == NULL)
		return (NULL);
	ft_printf("caca 4\n");
	res[name_len + value_len] = 0;
	ft_printf("caca 5\n");
	ft_strlcpy(res, var->name, name_len);
	ft_printf("caca 6\n");
	ft_strlcpy(res + name_len, " ", 1);
	ft_printf("caca 7\n");
	ft_strlcpy(res + name_len + 1, var->value, value_len);
	ft_printf("caca 8\n");
	return (res);
}
