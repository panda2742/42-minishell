/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:38:55 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/17 19:41:46 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	builtins_pwd(t_command	*c)
{
	char	*buffer;

	(void)c;
	buffer = getcwd(NULL, 0);
	write(1, buffer, ft_strlen(buffer));
	free(buffer);
	return (0);
}
