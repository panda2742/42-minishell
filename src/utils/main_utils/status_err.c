/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:49:19 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/14 14:27:21 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_excmd	*handle_status_err(t_err status, t_token *token, t_minishell *mini)
{
	if (status == ERR_MALLOC)
	{
		puterr(ft_sprintf(": error: Memory allocation error\n"), false);
		free_tokens(token);
		mini->last_status = 1;
		free_env(&mini->env);
		exit(EXIT_FAILURE);
	}
	else if (status == ERR_LEX)
	{
		free_tokens(token);
		mini->last_status = 2;
		return (NULL);
	}
	return (NULL);
}
