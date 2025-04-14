/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:26:44 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/14 16:01:35 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token *head_token)
{
	return (head_token->type == REDIR_IN || head_token->type == REDIR_OUT
		|| head_token->type == APPEND || head_token->type == HEREDOC);
}
