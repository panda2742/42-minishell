/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_del_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:26:54 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/09 22:26:56 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_word(void *content)
{
	t_word	*word;

	word = (t_word *)content;
	if (word->word)
		free(word->word);
	free(word);
}

void	del_redir(void *content)
{
	t_redir	*redir;

	redir = (t_redir *)content;
	if (redir->filename)
	{
		free(redir->filename);
	}
	free(redir);
}

void	del_cmds(void *content)
{
	t_cmds	*node;

	node = (t_cmds *)content;
	free(node);
}
