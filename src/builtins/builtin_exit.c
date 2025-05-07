/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:19 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/07 12:10:13 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		_free_before_exit(t_excmd *c);
static t_bool	_check_errors(t_excmd *c);

t_exit	builtin_exit(t_excmd *c)
{
	unsigned char		status;
	char				*arg;
	t_bool				free_at_end;

	status = (unsigned char)c->vars->minishell->last_status;
	if (c->argc == 1)
	{
		_free_before_exit(c);
		exit(status);
	}
	free_at_end = _check_errors(c);
	if (free_at_end)
	{
		_free_before_exit(c);
		exit(status);
	}
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

static t_bool	_check_errors(t_excmd *c)
{
	
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
