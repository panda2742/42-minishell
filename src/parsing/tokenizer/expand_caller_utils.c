/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_caller_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:05:02 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/09 15:56:56 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_error(t_token *token, t_minishell *mini,
				t_err status, t_token **new_tokens)
{
	if (status == ERR_MALLOC)
	{
		puterr(ft_sprintf(": error: Memory allocation error\n"), false);
		free_tokens(token);
		if (*new_tokens)
			free_tokens(*new_tokens);
		free_env(&mini->env);
		exit(EXIT_FAILURE);
	}
}

t_token	*get_tail(t_token *tok)
{
	if (tok == NULL)
	{
		return (tok);
	}
	while (tok->next)
		tok = tok->next;
	return (tok);
}
