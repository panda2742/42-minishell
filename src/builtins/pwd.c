/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:38:55 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/17 16:07:06 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	builtins_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	write(1, buffer, ft_strlen(buffer));
	free(buffer);
}
