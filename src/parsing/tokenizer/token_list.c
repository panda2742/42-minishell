/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:07:43 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/30 19:08:22 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_list(t_token *tokens)
{
	t_token		*tmp_token;
	// t_fragment	*tmp_frag;
	// t_fragment	*next_frag;

	while (tokens)
	{
		tmp_token = tokens;
		tokens = tokens->next;
		if (tmp_token->text)
			free(tmp_token->text);
		// tmp_frag = tmp_token->fragments;
		// while (tmp_frag)
		// {
		// 	next_frag = tmp_frag->next;
		// 	free(tmp_frag->text);
		// 	free(tmp_frag);
		// 	tmp_frag = next_frag;
		// }
		free(tmp_token);
	}
}


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
		free_tokens_list(head->tokens);
		free(head);
		head = tmp;
	}
}

t_token_list	*append_token_list(t_token_list **head_list, t_token **head_tokens)
{
	t_token_list	*tmp;
	t_token_list	*list;

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

static void
append_cmd_node(t_token_list **head, t_token_list *node)
{
    t_token_list *it;

    if (!*head)
        *head = node;
    else
    {
        it = *head;
        while (it->next)
            it = it->next;
        it->next = node;
    }
}

t_err	set_node_tok_list(t_token *orig, t_token *out)
{
	
	if (orig == NULL || out == NULL)
		return (ERR_MALLOC);
	out->type = orig->type;
	out->quote_type = orig->quote_type;
	out->next = NULL;
	if (orig->fragments && orig->fragments->text)
	{
		out->text = ft_strdup(orig->fragments->text);
		if (out->text == NULL)
			return (ERR_MALLOC);
	}
	else
		out->text = NULL;
	return (ERR_NONE);
}

void	update_head_tail(t_token_list_h *utils, t_token **new_token)
{
	if (utils->start == NULL)
		utils->start = *new_token;
	if (utils->end == NULL)
		utils->end = *new_token;
	else
	{
		utils->end->next = *new_token;
		utils->end = *new_token;
	}
}

/*
 * Add a new token list node to the linked list of token lists
 * The new node contains a list of tokens from start to end
 * The function returns the new token list node
*/

t_token_list	*add_token_list_node(t_token_list_h *u, t_token_list **head_list)				
{
	t_token_list	*list;
	t_token			*new_token;
	t_token			*tmp;
	t_err			status;
	t_token_list_h	utils;

	utils.start = NULL;
	utils.end = NULL;
	tmp = u->start;
	list = ft_memalloc(sizeof(t_token_list));
	if (list == NULL)
		return (NULL);
	while (tmp && tmp != u->end) 
	{
		new_token = ft_memalloc(sizeof(t_token));
		// free(new_token);
		// new_token = NULL;
		if (new_token == NULL)
			return (NULL);
		status = set_node_tok_list(tmp, new_token);
		if (status != ERR_NONE)
			return (NULL);
		update_head_tail(&utils, &new_token);
		tmp = tmp->next;
	}
	
	list->tokens = utils.start;
	list->next = NULL;
	append_cmd_node(head_list, list);
	return (list);
}

/*
 * Cut the token list at each TOKEN_PIPE 
 * and return the new struct for the command
 * End when TOKEN_PIPE or NULL is found
 * token_list_h is a struct to store the start end and current of the token list
 * tok_exp_h is token expand head
 * tok_cmd_h is the token command head we are building
*/
void	token_list(t_token *tok_exp_h, t_token_list **tok_cmd_h, t_minishell *mini)
{
	t_token_list_h	u;
	t_token_list	*node;

	(void)mini;
	(void)node;
	*tok_cmd_h = NULL;
	if (tok_exp_h == NULL)
		return ;
	u.current = tok_exp_h;
	while (u.current)
	{
		u.start = u.current;
		u.end = NULL;
		while (u.current && u.current->type != TOKEN_PIPE)
		{
			u.current = u.current->next;
			u.end = u.current;
		}
		// head_tokens = NULL;
		node = add_token_list_node(&u, tok_cmd_h);
		if (u.current && u.current->type == TOKEN_PIPE)
			u.current = u.current->next;
	}
}
