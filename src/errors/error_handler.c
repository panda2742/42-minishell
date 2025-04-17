/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:36 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/17 14:37:59 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	command_failure(t_excmd *c, char *message, t_bool call_perror)
{
	puterr(message, call_perror);
	c->status = EXIT_FAILURE;
	return (c->status);
}
