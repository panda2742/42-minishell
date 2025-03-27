
#include "minishell.h"

void	del_word(void *content)
{
	t_word *token;
	token = (t_word *)content;
	if (token->word)
		free(token->word);
	free(token);
}

void	del_redir(void *content)
{
	t_redir *token;
	token = (t_redir *)content;
	if (token->filename)
	{
		free(token->filename);
	}
	free(token);
}

void	del_cmds(void *content)
{
	t_cmds *node;
	node = (t_cmds *)content;

	free(node);
}

