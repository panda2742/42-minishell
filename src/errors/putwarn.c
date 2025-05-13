/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putwarn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:11:24 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/13 14:12:25 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	putwarn(char *message, t_bool call_perror)
{
	ft_putstr_fd(YELLOW PROJECT_NAME, 2);
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
			perror(": This is a simple warning (heap failure)");
		else
			ft_putstr_fd(": This is a simple warning (heap failure)\n", 2);
	}
	ft_putstr_fd(RESET, 2);
}
