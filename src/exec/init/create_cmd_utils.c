/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:30:50 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/12 15:32:32 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*free_redir_and_return_null(t_redir *redirect)
{
	free(redirect->filepath);
	free(redirect);
	return (NULL);
}

void	update_last_next(t_redir **last, t_redir *redirect)
{
	while ((*last)->next)
		*last = (*last)->next;
	(*last)->next = redirect;
}

t_excmd	*free_res_return_null(t_excmd *res)
{
	free(res);
	res = NULL;
	return (NULL);
}
