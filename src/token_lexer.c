
#include "minishell.h"

void del_token(void *content)
{
	t_token *token;

	token = (t_token *)content;
	if (token->value)
		free(token->value);
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

t_token *ft_create_token(t_token_type type, char *value, int quote_type,
						 t_token **head)
{
	t_token *new;
	t_token *tmp;
	static int i;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = ft_strdup(value);
	new->index = i;
	new->quote_type = quote_type;
	new->next = NULL;
	i++;
	// si head pointait vers NULL on l assigne au nouveau pointeur
	if (!*head)
		*head = new;
	// sinon on parcourt la liste et on ajoute new a la fin
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

void ft_print_tokens(t_token *head)
{
	while (head)
	{
		ft_printf("Token: Type = %d, Value = %s \n", head->type, head->value);
		head = head->next;
	}
}