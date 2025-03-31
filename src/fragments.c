
#include "minishell.h"

t_fragment *new_fragment(const char *start, size_t len, t_qtype quote_type)
{
	t_fragment	*new;

	new = malloc(sizeof(t_fragment));
	if (!new)
		return (NULL);
	new->text = malloc(sizeof(char) * (len + 1));
	if (!new->text)
	{
		free(new);
		return (NULL);
	}
	ft_memcpy(new->text, start, len);
	new->text[len] = '\0';
	new->quote_type = quote_type;
	new->next = NULL;
	return (new);
}

void	append_fragment(t_token *token, t_fragment *frag)
{
	t_fragment *tmp;

	if (!token->fragments) // token->fragments == head list
		token->fragments = frag;
	else
	{
		tmp = token->fragments;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = frag;
	}
}