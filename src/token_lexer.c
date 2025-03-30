
#include "minishell.h"

void free_fragments(t_fragment *frag)
{
	t_fragment *tmp;
	while (frag)
	{
		tmp = frag->next;
		free(frag->text);
		free(frag);
		frag = tmp;
	}
}

void del_token(void *content)
{
	t_token *token = (t_token *)content;
	free_fragments(token->fragments);
	free(token);
}


void token_clear(t_token **lst, void (*del)(void *))
{
	t_token *tmp;

	if (!lst || !del)
		return;
	while (*lst)
	{
		tmp = (*lst)->next;
		del(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void ft_create_token(t_token_type type, t_fragment *fragments, t_token **head)
{
	t_token *new = malloc(sizeof(t_token));
	if (!new)
		return;
	new->type = type;
	new->fragments = fragments;
	new->index = 0;
	new->next = NULL;

	if (!*head)
		*head = new;
	else
	{
		t_token *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}



void ft_print_tokens(t_token *head)
{
	while (head)
	{
		ft_printf("Token: Type = %d, Value = %s \n", head->type, head->fragments);
		head = head->next;
	}
}