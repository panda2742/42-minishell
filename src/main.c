/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/17 19:43:22 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**test_parsing(char *s)
{
	exec_command(s, NULL);
	return (NULL);
}

int	main(void)
{
	char	*line;
	char	**map;
	
	while (1)
	{
		ft_printf(BLUE "minishell$ " RESET);
		line = get_next_line(0);
		map = test_parsing(line);
		free(line);
	}
	(void)map;
	return (0);
}
