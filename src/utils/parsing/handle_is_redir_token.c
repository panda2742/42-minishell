/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_is_redir_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:04:34 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/15 23:04:43 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_is_redir_tokens(t_excmd *cmd, t_token *token)
{
	if (token->type == REDIR_IN)
		add_redirect(cmd, IN_REDIR, create_in_redirect(token->next->text));
	else if (token->type == REDIR_OUT)
		add_redirect (cmd, OUT_REDIR,
			create_out_redirect(token->next->text, false));
	else if (token->type == APPEND)
		add_redirect(cmd, OUT_REDIR,
			create_out_redirect(token->next->text, true));
	else if (token->type == HEREDOC)
		add_redirect(cmd, IN_REDIR,
			create_heredoc_redirect(token->next->text));
}
