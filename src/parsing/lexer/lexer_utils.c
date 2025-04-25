/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:02:28 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/23 14:25:18 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function checks if the character is a redirection or a pipe.
 * It returns 1 if it is, 0 otherwise.
*/
int	is_char_redir_or_pipe(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	print_tokens(t_token *tokens)
{
	t_token		*tmp_token;
	t_fragment	*tmp_frag;

	tmp_token = tokens;
	while (tmp_token)
	{
		printf("Token (type %d): ", tmp_token->type);
		tmp_frag = tmp_token->fragments;
		while (tmp_frag)
		{
			printf("[%s, quote %d] ", tmp_frag->text, tmp_frag->quote_type);
			tmp_frag = tmp_frag->next;
		}
		printf("\n");
		tmp_token = tmp_token->next;
	}
}
