/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:26:44 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/17 14:50:07 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token *head_token)
{
	return (head_token->type == TOKEN_REDIR_IN || head_token->type == TOKEN_REDIR_OUT
		|| head_token->type == TOKEN_APPEND || head_token->type == TOKEN_HEREDOC);
}
