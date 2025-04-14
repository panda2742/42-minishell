/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:04:41 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	heredoc(char *buffer, char *del, t_bool skip_writing)
{
	char	*line;

	(void)del;
	while (1)
	{
		line = readline("> ");
		if (buffer && !skip_writing)
			buffer = line;
		break ;
	}
	return (EXIT_SUCCESS);
}
