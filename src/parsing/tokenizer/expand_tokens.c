/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:42:29 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/22 11:49:16 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void incr_on_alnum(char *str, int *j)
{
	while (str[*j] && ft_isalnum(str[*j]))
		(*j)++;
}

void handle_last_rvalue(t_minishell *mini, t_utils *utils)
{
	char *value;

	value = ft_itoa(mini->last_status);
	if (!value)
	{
		free(utils->s1);
		mini->last_status = 2; /////////////////////
		return;
	}
	utils->s1 = str_join_free(utils->s1, value);
	utils->i = utils->j + 1;
	free(value);
}

void handle_expand_char(t_utils *utils, t_minishell *mini, char *input)
{
	t_env_var *env_var;
	char *var_name;
	char *value;

	utils->len1 = utils->j - utils->i - 1;
	var_name = ft_memalloc(utils->len1 + 1);
	utils->k = 0;
	while (utils->k < utils->len1)
	{
		var_name[utils->k] = input[utils->i + utils->k + 1];
		utils->k++;
	}
	var_name[utils->k] = '\0';
	env_var = get_var(&mini->env, var_name);
	if (env_var)
		value = ft_strdup(env_var->value);
	else
		value = ft_strdup("");
	free(var_name);
	utils->s1 = str_join_free(utils->s1, value);
	free(value);
	utils->i = utils->j;
}

void handle_normal_char(t_utils *utils, char *input)
{
	char tmp[2];

	tmp[0] = input[utils->i];
	tmp[1] = '\0';
	utils->s1 = str_join_free(utils->s1, tmp);
	utils->i++;
}

/*
 * Here we check if there is a $ in the fragmentstring
 * We use i and j to find the $ and the end of the variable
 * In handler functions we join everything in the string utils.s1
 * if there is no $ we joins the chars one by one
 */
char *expand_fragment(const char *input, int quote, t_minishell *mini)
{
	t_utils utils;

	ft_memset(&utils, 0, sizeof(t_utils));
	utils.s1 = ft_strdup("");
	if (!utils.s1)
		return (NULL);
	while (input[utils.i])
	{
		if (input[utils.i] == '$' && quote != QUOTE_SINGLE)
		{
			utils.j = utils.i + 1;
			incr_on_alnum((char *)input, &utils.j);
			if (input[utils.j] == '?')
				handle_last_rvalue(mini, &utils);
			else if (utils.j > utils.i + 1)
				handle_expand_char(&utils, mini, (char *)input);
		}
		else
			handle_normal_char(&utils, (char *)input);
	}
	return (utils.s1);
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
	token->fragments = ft_memalloc(sizeof(t_fragment));
	if (!token->fragments)
	{
		free(token);
		return (NULL);
	}
	token->fragments->text = ft_strdup(word);
	token->quote_type = set_qtype_fragment(token_head);
	token->fragments->quote_type = set_qtype_fragment(token_head);
	token->fragments->next = NULL;
	token->next = NULL;
	return (token);
}
void add_char_to_string(char *expanded, char **current, int *i)
{
	char tmp[2];

	tmp[0] = expanded[*i];
	tmp[1] = '\0';
	*current = str_join_free(*current, tmp);
	(*i)++;
}

void update_head_and_last(t_token *new_last, t_token *new_head, t_token *new_token)
{

	if (!new_head)
	{
		new_head = new_token;
		new_last = new_token;
	}
	else
	{
		new_last->next = new_token;
		new_last = new_token;
	}
}

typedef struct s_word_split {
	t_token	*new_head;
	t_token *new_last;
} t_word_split;

/*
 * New_head is the head of the new token list
 * New_last is the last token of the new token list
 * Current is the current string we are building
 * When we find a space we create a new token with the current string
 * and add it to the new token list
 */

static void process_unquoted_frag(const char *expanded, char **current,
								  t_word_split *new_list, t_token *token)
{
	int i;
	t_token *new_token;

	i = 0;
	while (expanded[i])
	{
		if (ft_isspace(expanded[i]))
		{
			if ((*current)[0] != '\0')
			{
				new_token = create_new_token_from_word(*current, token);
				update_head_and_last((new_list)->new_last, (new_list)->new_head, new_token);
				free(*current);
				*current = ft_strdup("");
			}
			while (expanded[i] && ft_isspace(expanded[i]))
				i++;
		}
		else
			add_char_to_string((char *)expanded, current, &i);
	}
}

void add_new_token(t_token **new_head, t_token **new_last, char *current, t_token *token)
{
	t_token *new_token;

	if (ft_strlen(current) > 0)
	{
		new_token = create_new_token_from_word(current, token);
		if (!new_token)
		{
			free(current);
			return;
		}
		if (!*new_head)
			*new_head = new_token;
		else
			(*new_last)->next = new_token;
		*new_last = new_token;
	}
}

/*
 * If strlen(current) > 0 we create a new token with the current string
 */


// void handle_quote_none(t_fragment *frag, t_minishell *mini, t_word_split *new_list)
// {
// 	char *expanded;
	
// }

t_token *word_split_token(t_token *token, t_minishell *mini)
{
	// t_token *new_head;
	// t_token *new_last;
	t_word_split new_list;
	t_fragment *frag;
	char *current;
	char *expanded;

	
	new_list.new_head = NULL;
	new_list.new_last = NULL;
	frag = token->fragments;
	current = ft_strdup("");

	while (frag)
	{
		if (frag->quote_type == QUOTE_NONE)
		{
			expanded = expand_fragment(frag->text, frag->quote_type, mini);
			if (!expanded)
			{
				free(current);
				return (NULL);
			}
			process_unquoted_frag(expanded, &current, &new_list, token);
			free(expanded);
		}
		else
		{
			if (frag->quote_type == QUOTE_DOUBLE)
				expanded = expand_fragment(frag->text, frag->quote_type, mini);
			else
				expanded = ft_strdup(frag->text);
			if (!expanded)
			{
				free(current);
				return (NULL);
			}
			current = str_join_free(current, expanded);
			free(expanded);
		}
		frag = frag->next;
	}
	add_new_token(&new_list.new_head, &new_list.new_last, current, token);
	free(current);
	return (new_list.new_head);
}
