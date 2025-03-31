#include "minishell.h"

char	**env_to_strlst(t_env_manager *env)
{
	char	**res;
	size_t	i;
	size_t	len;
	size_t	j[2];
	t_env_var	*var;

	res = malloc(sizeof(char *) * (env->env_size + 1));
	if (!res)
		return (NULL);
	i = -1;
	var = *env->vars;
	while (++i < env->env_size && var)
	{
		len = var->name_length + var->value_length + 1;

		res[i] = malloc(sizeof(char) * (len + 1));
		if (!res[i])
		{
			ft_free_strtab(res);
			return (NULL);
		}
		j[0] = -1;
		while (++j[0] < len)
			res[i][j[0]] = 'X';

		j[0] = -1;
		while (++j[0] < var->name_length)
			res[i][j[0]] = var->name[j[0]];

		j[1] = j[0];
		res[i][j[1]] = '=';

		while ((++j[1] - j[0] - 1) < var->value_length)
			res[i][j[1]] = var->value[j[1] - j[0] - 1];

		res[i][len] = 0;
		var = var->next;
	}
	res[i] = NULL;
	return (res);
}

