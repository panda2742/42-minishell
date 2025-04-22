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
	t_excmd			*cmd;
	t_excmd			*tmp;

	if (!c->in_a_child)
	{
		(void)cmd;
		(void)tmp;
		free_cmds(c->params->cmds);
		if (c->in_dup)
			sclose_fd(c->in_dup->fd, NULL);
		if (c->out_dup)
			sclose_fd(c->out_dup->fd, NULL);
		c->params->status = -2;
		return (c->params->status);
	}
	exit(EXIT_SUCCESS);
}
