/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:07:43 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/22 19:01:16 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Free the tokens in the list
 * The function will free all the tokens in the list
 * and then free the list itself
*/
void	free_tokens_in_list(t_token_list *head)
{
	t_token_list	*tmp;

	while (head)
	{
		tmp = head->next;
		free_tokens(head->tokens);
		free(head);
		head = tmp;
	}
}

t_token_list	*append_token_list(t_token_list **head_list,
		t_token_list *list, t_token **head_tokens)
{
	t_token_list	*tmp;

	if (!head_list || !head_tokens)
		return (NULL);
	list = ft_memalloc(sizeof(t_token_list));
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
 * Add a new token list node to the linked list of token lists
 * The new node contains a list of tokens from start to end
 * The function returns the new token list node
*/

t_token_list	*add_token_list_node(t_token *start, t_token *end,
					t_token_list **head_list, t_token **head_tokens)
{
	t_token_list	*list;
	t_token			*new_token;
	t_token			*tmp_token;

	tmp_token = start;
	list = NULL;
	while (tmp_token != end)
	{
		new_token = ft_create_token(tmp_token->type);
		new_token->next = NULL;
		append_token(head_tokens, new_token);
		new_token->type = tmp_token->type;
		if (tmp_token->fragments && tmp_token->fragments->text)
		{
			new_token->text = ft_strdup(tmp_token->fragments->text);
			if (new_token->text == NULL)
				return (NULL);
		}
		else
			new_token->text = NULL;
		new_token->quote_type = tmp_token->quote_type;
		tmp_token = tmp_token->next;
	}
	list = append_token_list(head_list, list, head_tokens);
	return (list);
}

/*
 * Cut the token list at each TOKEN_PIPE 
 * and return the new struct for the command
 * End when TOKEN_PIPE or NULL is found
*/
void	token_list(t_token *head_token, t_token_list **head_list)
{
	t_token	*current;
	t_token	*start;
	t_token	*end;
	t_token	*head_tokens;

	*head_list = NULL;
	if (head_token == NULL)
		return ;
	current = head_token;
	while (current)
	{
		start = current;
		end = NULL;
		while (current && current->type != TOKEN_PIPE)
		{
			current = current->next;
			end = current;
		}
		head_tokens = NULL;
		add_token_list_node(start, end, head_list, &head_tokens);
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
}
