#include "minishell.h"

char *expand_fragment(const char *input, int quote, t_env_manager *env)
{
	t_utils utils;
	t_env_var *env_var;

	ft_memset(&utils, 0, sizeof(t_utils));
	utils.s1 = ft_strdup("");
    while (input[utils.i])
    {
        if (input[utils.i] == '$' && quote != SINGLE) // Si pas entre quotes simple
        {
            utils.j = utils.i + 1;
            while (input[utils.j] && ((ft_isalnum(input[utils.j]) || input[utils.j] == '_')))
                utils.j++;
            if (utils.j > utils.i + 1)
            {
                utils.len1 = utils.j - utils.i - 1;
                char *var_name = malloc(utils.len1 + 1);
                utils.k = 0;
                while (utils.k < utils.len1)
                {
                    var_name[utils.k] = input[utils.i + 1 + utils.k];
                    utils.k++;
                }
                var_name[utils.k] = '\0';
                /* on recupere la variable dans notre env manager */
                env_var = get_var(env, var_name);
                char *value;
                if (env_var)
                    value = ft_strdup(env_var->value);
                else
                    value = ft_strdup("");
                free(var_name);
                utils.s1 = str_join_free(utils.s1, value);
                free(value);
                utils.i = utils.j;
                continue;
            }
        }
        {
            char tmp[2];
            tmp[0] = input[utils.i];
            tmp[1] = '\0';
            utils.s1 = str_join_free(utils.s1, tmp);
        }
        utils.i++;
    }
    return utils.s1;
}

// char *expand_token(t_token *token, t_env_manager *env)
// {
//     char *result = ft_strdup("");
//     if (!result)
//         return NULL;
//     t_fragment *frag = token->fragments;
//     while (frag)
//     {
//         char *expanded;
//         if (frag->quote_type == 1) /* SINGLE quotes : aucun expansion */
//             expanded = ft_strdup(frag->text);
//         else
//             expanded = expand_fragment(frag->text, frag->quote_type, env);
//         if (!expanded) 
// 		{ 
// 			free(result); 
// 			return NULL; 
// 		}
//         result = str_join_free(result, expanded);
//         free(expanded);
//         frag = frag->next;
//     }
//     return result;
// }

// void expand_all_tokens(t_token *tokens, t_env_manager *env)
// {
//     t_token *tmp = tokens;
//     while (tmp)
//     {
//         char *exp = expand_token(tmp, env);
//         printf("Expanded token: %s\n", exp);
//         free(exp);
//         tmp = tmp->next;
//     }
// }

t_qtype set_qtype_fragment(t_token *token_head)
{
	t_fragment *tmp;

	tmp = token_head->fragments;
	while (tmp)
	{
		if (tmp->quote_type == DOUBLE)
			return (DOUBLE);
		tmp = tmp->next;
	}
	return (NONE);
}

static t_token *create_new_token_from_word(const char *word, t_token *token_head)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = token_head->type;
    token->index = 0;
    token->fragments = malloc(sizeof(t_fragment));
    if (!token->fragments)
    {
		free(token);
        return (NULL);
    }
    token->fragments->text = ft_strdup(word);
    token->fragments->quote_type = set_qtype_fragment(token_head);
    token->fragments->next = NULL;
    token->next = NULL;
    return (token);
}

static void process_unquoted_fragment(const char *expanded, char **current, t_token **new_head, t_token **new_last, t_token *token)
{
    int i;
	t_token *new_token;

	i = 0;
    while (expanded[i])
    {
        if (ft_isspace(expanded[i]))
        {
            /* Si current n'est pas vide, on le finalise */
            if ((*current)[0] != '\0')
            {
                new_token = create_new_token_from_word(*current, token);
                if (!*new_head)
                {
                    *new_head = new_token;
                    *new_last = new_token;
                }
                else
                {
                    (*new_last)->next = new_token;
                    *new_last = new_token;
                }
                free(*current);
                *current = ft_strdup("");
            }
            /* Sauter tous les separateurs */
            while (expanded[i] && ft_isspace(expanded[i]))
                i++;
        }
        else
        {
            char tmp[2];
            tmp[0] = expanded[i];
            tmp[1] = '\0';
            *current = str_join_free(*current, tmp);
            i++;
        }
    }
}

t_token *word_split_token(t_token *token, t_env_manager *env)
{
    t_token *new_head;
    t_token *new_last;
    t_fragment *frag;
    char *current;
	
	new_head = NULL;
	new_last = NULL;
	frag = token->fragments;
	current = ft_strdup("");
    while (frag)
    {
        char *expanded;
        if (frag->quote_type == NONE)
        {
            expanded = expand_fragment(frag->text, frag->quote_type, env);
            if (!expanded) 
			{ 
				free(current); 
				return (NULL); 
			}
            process_unquoted_fragment(expanded, &current, &new_head, &new_last, token);
            free(expanded);
        }
        else
        {
            /* Pour DOUBLE quotes, on effectue quand meme l'expansion,
               et pour SINGLE, on fait un strdup */
            if (frag->quote_type == DOUBLE)
                expanded = expand_fragment(frag->text, frag->quote_type, env);
            else
                expanded = ft_strdup(frag->text);
            if (!expanded) 
			{ 
				free(current); 
				return (NULL); 
			}
            /* Simple concatenation pour les fragments cites */
            current = str_join_free(current, expanded);
            free(expanded);
        }
        frag = frag->next;
    }
	// Only add if there is someting in current to prevent $var="a b   " to add an empty token
	if (ft_strlen(current) > 0)
	{
		t_token *new_token = create_new_token_from_word(current, token);
		if (!new_token) 
		{ 
			free(current);
			return (new_head);
		}
		if (!new_head)
        	new_head = new_token;
		else
    	    new_last->next = new_token;
	}
    free(current);
    return (new_head);
}
