/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:14 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:47:14 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	builtin_echo(t_excmd *c)
{
	printf(MAGENTA "<'echo' builtin to code>\n" RESET);
	(void)c;
	return (0);
}
