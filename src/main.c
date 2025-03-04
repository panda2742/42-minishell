/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/04 15:56:28 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**test_parsing(char *s)
{
	char	**mapped;
	int	i;
	
	i = 0;
	mapped = ft_split(s, ' ');
	while (mapped[i])
	{
		ft_printf("%s\n", mapped[i]);
		i++;
	}
	return (mapped);
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
	return (0);
}
