/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:02:28 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/17 09:02:32 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* renvoie  positif si c == quelque chose */
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
