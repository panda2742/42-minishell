
#include "minishell.h"

void *get_next_token(void *node)
{
	if (!node)
		return NULL;
	return (((t_token *)node)->next);
}

void	*get_next_cmds(void *node)
{
	if (!node)
		return NULL;
	return (((t_cmds *)node)->next);
}

void	*get_next_word(void *node)
{
	if (!node)
		return NULL;
	return (((t_word *)node)->next);
}

void	*get_next_redir(void *node)
{
	if (!node)
		return NULL;
	return (((t_redir *)node)->next);
}