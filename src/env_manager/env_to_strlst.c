/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_strlst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:31 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:02:12 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_fill_var(t_env_var *var, char *res, size_t len);

char	**env_to_strlst(t_env_manager *env)
{
	char		**res;
	size_t		i;
	size_t		len;
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
		res[i] = _fill_var(var, res[i], len);
		var = var->next;
	}
	res[i] = NULL;
	return (res);
}

static char	*_fill_var(t_env_var *var, char *res, size_t len)
{
	size_t		j[2];

	j[0] = -1;
	while (++j[0] < var->name_length)
		res[j[0]] = var->name[j[0]];
	j[1] = j[0];
	res[j[1]] = '=';
	while ((++j[1] - j[0] - 1) < var->value_length)
		res[j[1]] = var->value[j[1] - j[0] - 1];
	res[len] = 0;
	return (res);
}
