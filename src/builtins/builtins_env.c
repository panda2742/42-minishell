#include "minishell.h"

static t_bool	_write_var(t_env_var *var);

t_exit	builtins_env(t_excmd *c)
{
	size_t	i;
	t_env_var	*var;

	i = -1;
	var = *c->env->vars;
	while (++i < c->env->env_size && var)
	{
		if (!var->name || !var->value)
		{
			var = var->next;
			continue ;
		}
		if (!_write_var(var))
		{
			c->status = EXIT_FAILURE;
			break ;
		}
		var = var->next;
	}
	return (c->status);
}

static t_bool	_write_var(t_env_var *var)
{
	if (write(1, U_BLUE, 7) == -1)
		return (false);
	if (write(1, var->name, ft_strlen(var->name)) == -1)
		return (false);
	if (write(1, RESET, 5) == -1)
		return (false);
	if (write(1, "=", 1) == -1)
		return (false);
	if (write(1, var->value, ft_strlen(var->value)) == -1)
		return (false);
	if (write(1, "\n", 1) == -1)
		return (false);
	return (true);
}
