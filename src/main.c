/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/18 14:42:49 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**test_parsing(char *s)
{
	char	*command_name;

	/* Remplace cette instruction la par ton call de parsing */
	/* TODO */
	command_name = s;

	exec_command(command_name, NULL);
	return (NULL);
}

int	main(void)
{
	char	*line;
	char	**map;
	
	while (1)
	{
		show_prompt();
		line = readline(" ");
		map = test_parsing(line);
		free(line);
	}
	(void)map;
	return (0);
}
