/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_is_redir_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:04:34 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/23 14:47:52 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Helper function to handle the redirections.
 * It is called when we find a redirection in the token list.
 * It adds the redirection to the cmd struct.
*/
void	handle_is_redir_tokens(t_excmd *cmd, t_token *token)
{
	if (token->type == TOKEN_REDIR_IN)
		add_redirect(cmd, IN_REDIR, create_in_redirect(token->next->text));
	else if (token->type == TOKEN_REDIR_OUT)
		add_redirect (cmd, OUT_REDIR,
			create_out_redirect(token->next->text, false));
	else if (token->type == TOKEN_APPEND)
		add_redirect(cmd, OUT_REDIR,
			create_out_redirect(token->next->text, true));
	else if (token->type == TOKEN_HEREDOC)
		add_redirect(cmd, IN_REDIR,
			create_heredoc_redirect(token->next->text));
}
