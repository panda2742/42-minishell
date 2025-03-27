
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
void lst_clear(void **lst, void *(*get_next)(void *), void (*del)(void *))
{
	t_token *tmp;
	
	if (!lst || !*lst || !get_next || !del)
		return ;
	while (*lst)
	{
		tmp = get_next(*lst);
		del(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}