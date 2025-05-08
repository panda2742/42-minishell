/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:38 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/08 15:26:43 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	puterr(char *message, t_bool call_perror)
{
	ft_putstr_fd(RED PROJECT_NAME, 2);
	if (message)
	{
		if (call_perror)
			perror(message);
		else
			ft_putstr_fd(message, 2);
		free(message);
	}
	else
	{
		if (call_perror)
			perror(": An error occurred (heap failure)");
		else
			ft_putstr_fd(": An error occurred (heap failure)\n", 2);
	}
	ft_putstr_fd(RESET, 2);
}
