
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

