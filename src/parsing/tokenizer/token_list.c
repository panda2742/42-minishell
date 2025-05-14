/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:07:43 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 14:28:44 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*append_token_list(t_token_list **head_list,
					t_token **head_tokens)
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

/*
 * Add a new token list node to the linked list of token lists
 * The new node contains a list of tokens from start to end
 * The function returns the new token list node
*/

t_token_list	*add_token_list_node(t_token_list_h *u,
					t_token_list **head_list)
{
	t_token_list	*list;
	t_token			*new_token;
	t_token			*tmp;
	t_err			status;
	t_token_list_h	utils;

	set_values(&utils);
	tmp = u->start;
	list = ft_memalloc(sizeof(t_token_list));
	if (list == NULL)
		return (NULL);
	while (tmp && tmp != u->end)
	{
		new_token = ft_memalloc(sizeof(t_token));
		if (new_token == NULL)
			return (add_token_failed(list, new_token));
		status = set_node_tok_list(tmp, new_token);
		if (status != ERR_NONE)
			return (add_token_failed(list, new_token));
		update_head_tail(&utils, &new_token, &tmp);
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

void	token_list(t_token *tok_exp_h, t_token_list **tok_cmd_h,
					t_minishell *mini)
{
	t_token_list_h	u;
	t_token_list	*node;

	(void)mini;
	node = NULL;
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
		node = add_token_list_node(&u, tok_cmd_h);
		if (node == NULL)
			exit_node_failed(mini, tok_cmd_h, tok_exp_h);
		if (u.current && u.current->type == TOKEN_PIPE)
			u.current = u.current->next;
	}
}
