
#include "minishell.h"

void	free_tokens_in_list(t_token *tokens, t_token_list *list)
{
	t_token			*next_token;
	t_token_list	*next_list;


	while (list)
	{
		next_list = list->next;
		free(list);
		list = next_list;
		while (tokens)
		{
			next_token = tokens->next;
			free(tokens->text);
			free(tokens);
			tokens = next_token;
		}
	}
	
}


// Je veux creer une nouvelle liste chainee de type t_token_list
// elle contiendra un pointeur vers next 
// et un pointeur vers une nouvelle liste chainee t_token
// pour chaque liste de t_token je dois redefinir sa head, faire pointer son dernier element vers NULL
// donc je vais boucler depuis start jusqu a end pour recopier chaque node un a un

t_token_list	*add_token_list_node(t_token *start, t_token *end, t_token_list **head_list, t_token **head_tokens)
{
	t_token_list 	*list;
	t_token_list 	*tmp;
	t_token			*new_token;
	t_token			*tmp_token;
	
	tmp_token = start;
	while (tmp_token != end)
	{
		new_token = ft_create_token(tmp_token->type);
		new_token->next = NULL;
		append_token(head_tokens, new_token);
		new_token->type = tmp_token->type;
		if (tmp_token->fragments && tmp_token->fragments->text)
		{
			new_token->text = ft_strdup(tmp_token->fragments->text);  // Malloc
			if (new_token->text == NULL)
				return (NULL);
		}
		else
			new_token->text = NULL;
		new_token->quote_type = tmp_token->quote_type;
		tmp_token = tmp_token->next;
	}
	list = malloc(sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->tokens = *head_tokens;
	list->next = NULL;
	if (*head_list == NULL)
		*head_list = list;
	else
	{
		tmp = *head_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = list;
	}
	return (list);
}
/*
 * Cut the token list at each PIPE and return the new struct for the command
*/
void	token_list(t_token *head_token, t_token_list **head_list)
{
	t_token *current;
	t_token	*start;
	t_token *end;
	t_token_list *token_list;
	
	*head_list = NULL;
	current = head_token;
	while (current)
	{
		start = current;
		end = NULL;
		while (current && current->type != PIPE)
		{
			current = current->next;
			end = current;
		}
		t_token *head_tokens = NULL;
		token_list = add_token_list_node(start, end, head_list, &head_tokens);
		if (current && current->type == PIPE)
			current = current->next;
	}
}
