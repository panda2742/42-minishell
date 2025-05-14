/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:45:45 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 13:50:48 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	display_colors(t_excmd *cmd)
{
	return (cmd->next == NULL && cmd->out_redirects.size == 0
				&& isatty(STDOUT_FILENO));
}

static t_env_var	*_merge_sorted_lists(t_env_var *a, t_env_var *b)
{
	t_env_var *result = NULL;

	if (!a) return b;
	if (!b) return a;

	if (ft_strcmp(a->name, b->name) <= 0)
	{
		result = a;
		result->next = _merge_sorted_lists(a->next, b);
	}
	else
	{
		result = b;
		result->next = _merge_sorted_lists(a, b->next);
	}
	return result;
}

static void	_split_list(t_env_var *source, t_env_var **front_ref, t_env_var **back_ref)
{
	t_env_var *slow = source;
	t_env_var *fast = source->next;

	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	*front_ref = source;
	*back_ref = slow->next;
	slow->next = NULL;
}

void sort_env_list(t_env_var **head_ref)
{
	t_env_var *head = *head_ref;
	t_env_var *a;
	t_env_var *b;

	if (!head || !head->next)
		return;

	_split_list(head, &a, &b);

	sort_env_list(&a);
	sort_env_list(&b);

	*head_ref = _merge_sorted_lists(a, b);
}
