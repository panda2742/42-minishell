/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:19 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:47:14 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	builtin_exit(t_excmd *c)
{
	(void)c;
	free_env(c->env);
	ft_free_strtab(c->argv);
	exit(c->status);
}
