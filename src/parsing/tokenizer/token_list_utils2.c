/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:54:09 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/09 15:56:00 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*add_token_failed(t_token_list *list, t_token *new_token)
{
	free(list);
	if (new_token)
		free(new_token);
	return (NULL);
}

void	set_values(t_token_list_h *utils)
{
	utils->start = NULL;
	utils->end = NULL;
}
