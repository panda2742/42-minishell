/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:14 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/22 18:40:20 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	builtin_echo(t_excmd *c)
{
	int		i;
	char	**av;

	i = -1;
	av = c->argv;
	av++;
	c->argc--;
	if (c->argc == 0)
		return (0);
	while (++i < c->argc)
	{
		if (!av[i])
			break ;
		printf("%s", av[i]);
		if (i < c->argc - 1)
			printf(" ");
	}
	printf("\n");
	return (EXIT_SUCCESS);
}
