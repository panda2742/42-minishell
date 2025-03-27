
#include "minishell.h"

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