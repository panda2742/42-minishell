/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:14 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/21 14:29:15 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	builtin_echo(t_excmd *c)
{
	int	i;

	i = -1;
	c->argv++;
	c->argc--;
	if (c->argc == 0)
		return (0);
	while (++i < c->argc)
	{
		printf("%s", c->argv[i]);
		if (i < c->argc - 1)
			printf(" ");
	}
	printf("\n");
	return (0);
}
