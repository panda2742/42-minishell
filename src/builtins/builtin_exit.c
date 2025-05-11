/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:19 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/11 13:49:22 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		_free_before_exit(t_excmd *c);
static t_bool	_check_errors(t_excmd *c, unsigned char *status);
static t_bool	_is_numeric_only(char *nptr);

t_exit	builtin_exit(t_excmd *c)
{
	unsigned char	status;
	t_bool			free_at_end;

	if (isatty(STDOUT_FILENO))
		ft_printf("exit\n");
	status = (unsigned char)c->vars->minishell->last_status;
	if (c->argc == 1)
	{
		_free_before_exit(c);
		exit(status);
	}
	free_at_end = _check_errors(c, &status);
	if (free_at_end)
	{
		_free_before_exit(c);
		exit(status);
	}
	return (0);
}

static void	_free_before_exit(t_excmd *c)
{
	t_excmd	**cmds;

	cmds = c->vars->cmds;
	ft_free_strtab(c->vars->minishell->env.envlst);
	free_env(&c->vars->minishell->env);
	free(c->vars);
	free_cmds(cmds);
}

static t_bool	_check_errors(t_excmd *c, unsigned char *status)
{
	size_t	i;

	i = 0;
	while (c->argv[++i])
	{
		if (_is_numeric_only(c->argv[i]) == false)
		{
			puterr(ft_sprintf(": exit: %s: numeric argument required\n",
				c->argv[i]), false);
			*status = EXIT_PARSING;
			return (true);
		}
	}
	if (c->argc == 2)
	{
		*status = (unsigned char)ft_atoi(c->argv[1]);
		return (true);
	}
	puterr(ft_sprintf(": exit: too many arguments\n"), false);
	return (false);
}

static t_bool	_is_numeric_only(char *nptr)
{
	while (*nptr)
	{
		if (ft_isdigit(*nptr) == false)
			return (false);
		nptr++;
	}
	return (true);
}
