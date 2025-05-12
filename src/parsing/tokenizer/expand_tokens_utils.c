/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:26:31 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/12 14:48:05 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Here we check if there is a double quote in the fragments
 * If there is one we set the quote type to QUOTE_DOUBLE
 */

t_qtype	set_qtype_fragment(t_token *token_head)
{
	t_fragment	*tmp;

	tmp = token_head->fragments;
	while (tmp)
	{
		if (tmp->quote_type == QUOTE_DOUBLE)
			return (QUOTE_DOUBLE);
		tmp = tmp->next;
	}
	return (QUOTE_NONE);
}

void	update_head_and_last(t_token **new_h, t_token **new_t,
	t_token *new_token)
{
	if (!*new_h)
		*new_h = new_token;
	else
		(*new_t)->next = new_token;
	*new_t = new_token;
}

t_err	handle_last_rvalue(t_minishell *mini, t_utils *utils)
{
	char	*value;
	char	*tmp;

	value = ft_itoa(mini->last_status);
	if (!value)
	{
		free(utils->s1);
		return (ERR_MALLOC);
	}
	tmp = str_join_free(utils->s1, value);
	free(value);
	if (!tmp)
		return (ERR_MALLOC);
	utils->s1 = tmp;
	utils->i = utils->j + 1;
	return (ERR_NONE);
}

void	set_var_name(t_utils *utils, char *var_name, char *input)
{
	utils->k = 0;
	while (utils->k < utils->len1)
	{
		var_name[utils->k] = input[utils->i + utils->k + 1];
		utils->k++;
	}
	var_name[utils->k] = '\0';
}

t_err	handle_expand_char(t_utils *utils, t_minishell *mini, char *input)
{
	t_env_var	*env_var;
	char		*var_name;
	char		*value;
	char		*tmp;

	utils->len1 = utils->j - utils->i - 1;
	var_name = ft_memalloc(utils->len1 + 1);
	if (!var_name)
		return (ERR_MALLOC);
	set_var_name(utils, var_name, input);
	env_var = get_var(&mini->env, var_name);
	if (env_var)
		value = ft_strdup(env_var->value);
	else
		value = ft_strdup("");
	free(var_name);
	if (value == NULL)
		return (ERR_MALLOC);
	tmp = str_join_free(utils->s1, value);
	free(value);
	if (tmp == NULL)
		return (ERR_MALLOC);
	utils->s1 = tmp;
	utils->i = utils->j;
	return (ERR_NONE);
}
