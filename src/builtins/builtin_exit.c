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
	const t_exit	status = c->status;
	t_excmd			*cmd;
	t_excmd			*tmp;

	ft_free_strtab(c->env->envlst);
	free_env(c->env);
	cmd = c;
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		tmp = cmd->next;
		free_one_cmd(cmd);
		cmd = tmp;
	}
	exit(status);
}
