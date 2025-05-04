/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:42:29 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/29 16:09:00 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_err handle_last_rvalue(t_minishell *mini, t_utils *utils)
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

t_err handle_expand_char(t_utils *utils, t_minishell *mini, char *input)
{
	t_env_var *env_var;
	char *var_name;
	char *value;
	char	*tmp;

	utils->len1 = utils->j - utils->i - 1;
	var_name = ft_memalloc(utils->len1 + 1);
	if (!var_name)
		return (ERR_MALLOC);
	utils->k = 0;
	while (utils->k < utils->len1)
	{
		var_name[utils->k] = input[utils->i + utils->k + 1];
		utils->k++;
	}
	var_name[utils->k] = '\0';
	env_var = get_var(&mini->env, var_name);
	free(var_name);
	if (env_var)
		value = ft_strdup(env_var->value);
	else
		value = ft_strdup("");
	if (value == NULL)
	{
		free(utils->s1);
		return (ERR_MALLOC);
	}
	tmp = str_join_free(utils->s1, value);
	free(value);
	if (tmp == NULL)
		return (ERR_MALLOC);
	utils->s1 = tmp;
	utils->i = utils->j;
	return (ERR_NONE);
}

/*
 * Here we check if there is a $ in the fragmentstring
 * We use i and j to find the $ and the end of the variable
 * In handler functions we join everything in the string utils.s1
 * if there is no $ we joins the chars one by one
 */
char *expand_fragment(const char *input, int quote, t_minishell *mini)
{
    t_utils u;
    t_err   st;

    ft_memset(&u, 0, sizeof(u));
    u.s1 = ft_strdup("");
    if (!u.s1)
        return (NULL);

    while (input[u.i])
    {
        if (input[u.i] == '$' && quote != QUOTE_SINGLE)
        {
            u.j = u.i + 1;
            incr_on_alnum((char *)input, &u.j);
            if (input[u.j] == '?')
                st = handle_last_rvalue(mini, &u);
            else if (u.j > u.i + 1)
                st = handle_expand_char(&u, mini, (char *)input);
            else
                /* dollar isolé, traité comme caractère normal */
                st = handle_normal_char(&u, (char *)input);
        }
        else
        {
            st = handle_normal_char(&u, (char *)input);
        }

        if (st != ERR_NONE)
        {
            free(u.s1);
            return (NULL);
        }
    }
    return (u.s1);
}

/*
 * Here we check if there is a double quote in the fragments
 * If there is one we set the quote type to QUOTE_DOUBLE
 */

t_qtype set_qtype_fragment(t_token *token_head)
{
	t_fragment *tmp;

	tmp = token_head->fragments;
	while (tmp)
	{
		if (tmp->quote_type == QUOTE_DOUBLE)
			return (QUOTE_DOUBLE);
		tmp = tmp->next;
	}
	return (QUOTE_NONE);
}

static t_token *create_new_token_from_word(const char *word,
										   t_token *token_head)
{
	t_token *token;

	token = ft_memalloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_head->type;
	token->index = 0;
	token->next = NULL;
	token->quote_type = set_qtype_fragment(token_head);
	token->fragments = ft_memalloc(sizeof(t_fragment));
	if (!token->fragments)
	{
		free(token);
		return (NULL);
	}
	token->fragments->text = ft_strdup(word);
	if (!token->fragments->text)
	{
		free(token->fragments);
		free(token);
		return (NULL);
	}
	token->fragments->quote_type = set_qtype_fragment(token_head);
	token->fragments->next = NULL;
	return (token);
}

void update_head_and_last(t_token **new_h, t_token **new_t,
						  t_token *new_token)
{
	if (!*new_h)
		*new_h = new_token;
	else
		(*new_t)->next = new_token;
	*new_t = new_token;
}

/*
 * new_h is the head of the new token list
 * new_t is the last token of the new token list
 * Current is the current string we are building
 * When we find a space we create a new token with the current string
 * and add it to the new token list
 */

t_err process_unquoted_frag(const char *expanded, char **current,
							t_w_split **new_list, t_token *token)
{
	int i;
	t_token *n_tok;
	t_err	st;

	i = 0;
	while (expanded[i])
	{
		if (ft_isspace(expanded[i]))
		{
			if ((*current)[0] != '\0')
			{
				n_tok = create_new_token_from_word(*current, token);
				// (void)token; test malloc
				// n_tok = NULL; 
				if (!n_tok)
					return (ERR_MALLOC);
				update_head_and_last(&(*new_list)->new_h, &(*new_list)->new_t, n_tok);
				free(*current);
				*current = ft_strdup("");
				if (*current == NULL)
					return (ERR_MALLOC);
			}
			while (expanded[i] && ft_isspace(expanded[i]))
				i++;
		}
		else
		{
			st = add_char_to_string((char *)expanded, current, &i);
			if (st != ERR_NONE)
				return (st);
		}
			
	}
	return (ERR_NONE);
}

t_token *add_new_token(t_token **new_h, t_token **new_t,
					   char *current, t_token *token)
{
	t_token *new_token;

	new_token = create_new_token_from_word(current, token);
	if (!new_token)
		return (NULL);
	if (!*new_h)
		*new_h = new_token;
	else
		(*new_t)->next = new_token;
	*new_t = new_token;

	return (new_token);
}
