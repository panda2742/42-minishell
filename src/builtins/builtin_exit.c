/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:19 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/16 12:45:18 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	builtin_exit(t_excmd *c)
{
	t_excmd			**cmds;

	cmds = c->vars->cmds;
	ft_free_strtab(c->vars->minishell->env.envlst);
	free_env(&c->vars->minishell->env);
	free(c->vars);
	free_cmds(cmds);
	exit(EXIT_SUCCESS);
}
