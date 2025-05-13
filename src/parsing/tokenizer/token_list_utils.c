/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:39:29 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/09 15:58:40 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_list(t_token *tokens)
{
	t_token		*tmp_token;

	while (tokens)
	{
		tmp_token = tokens;
		tokens = tokens->next;
		if (tmp_token->text)
			free(tmp_token->text);
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

void	update_head_tail(t_token_list_h *utils, t_token **new_token,
							t_token **tmp)
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
	*tmp = (*tmp)->next;
}

/*
 * Append a new token list node to the linked list of token lists
*/

void	append_cmd_node(t_token_list **head, t_token_list *node)
{
	t_token_list	*new_tok;

	if (!*head)
		*head = node;
	else
	{
		new_tok = *head;
		while (new_tok->next)
			new_tok = new_tok->next;
		new_tok->next = node;
	}
}

void	exit_node_failed(t_minishell *mini, t_token_list **tok_cmd_h,
	t_token *tok_exp_h)
{
	free_tokens(tok_exp_h);
	free_tokens_in_list(*tok_cmd_h);
	free_env(&mini->env);
	puterr(ft_sprintf(": error: Memory allocation error (token_list)\n"),
		false);
	exit(EXIT_FAILURE);
}
