/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:36 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/16 16:46:40 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*handle_env_mem_alloc(t_env_manager *env)
{
	free_env(env);
	return (NULL);
}

t_exit	command_failure(t_excmd *c, char *message, t_bool call_perror)
{
	puterr(message, call_perror);
	c->status = EXIT_FAILURE;
	return (c->status);
}
