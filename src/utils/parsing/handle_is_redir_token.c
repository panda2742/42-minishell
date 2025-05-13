/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_is_redir_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:04:34 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/09 16:00:06 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Helper function to handle the redirections.
 * It is called when we find a redirection in the token list.
 * It adds the redirection to the cmd struct.
*/
int	handle_is_redir_tokens(t_excmd *cmd, t_token *token)
{
	if (token->type == TOKEN_REDIR_IN)
	{
		if (!add_redirect(cmd, IN_REDIR,
				create_in_redirect(token->next->text)))
			return (0);
	}
	else if (token->type == TOKEN_REDIR_OUT)
	{
		if (!add_redirect (cmd, OUT_REDIR,
				create_out_redirect(token->next->text, false)))
			return (0);
	}
	else if (token->type == TOKEN_APPEND)
	{
		if (!add_redirect(cmd, OUT_REDIR,
				create_out_redirect(token->next->text, true)))
			return (0);
	}
	else if (token->type == TOKEN_HEREDOC)
	{
		if (!add_redirect(cmd, IN_REDIR,
				create_heredoc_redirect(token->next->text)))
			return (0);
	}
	return (1);
}
