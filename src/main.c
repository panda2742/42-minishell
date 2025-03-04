/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/04 15:30:28 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_parsing(char *s)
{
	// test ton parsing ici
	(void)s;
}

int	main(void)
{
	char	*line;

	while (1)
	{
		ft_printf(BLUE "minishell$ " RESET);
		line = get_next_line(0);
		test_parsing(line);
		free(line);
	}
	return (0);
}
