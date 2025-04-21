/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:36 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/21 16:23:23 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	command_failure(t_excmd *c, char *message, t_bool call_perror)
{
	puterr(message, call_perror);
	c->status = EXIT_FAILURE;
	return (c->status);
}
