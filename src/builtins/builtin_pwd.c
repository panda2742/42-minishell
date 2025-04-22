/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:23 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:47:14 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	builtin_pwd(t_excmd	*c)
{
	char	*buffer;

	(void)c;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
		return (EXIT_FAILURE);
	if (ft_putstr_fd(buffer, 1) == -1)
	{
		free(buffer);
		return (EXIT_FAILURE);
	}
	free(buffer);
	if (ft_putstr_fd("\n", 1) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
