

#include "minishell.h"
#include <string.h>

void append_token_exp(t_token_exp **head, t_token_exp *new_node)
{
    t_token_exp *tmp;

    if (!*head)
    {
		*head = new_node;
        return;
    }
    tmp = *head;
	tmp->next = NULL;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

char *append_char(char c, char *string)
{
	char tmp_char[2];
	char *tmp;

	tmp_char[0] = c;
	tmp_char[1] = '\0';
	tmp = ft_strjoin(string, tmp_char);
	return (tmp);
}

char *join_and_free(char *str)
{
	char *tmp;

	tmp = ft_strjoin(str, "$");
	free(str);
	return (tmp);
}

char *free_str_and_return(char *str)
{
	free(str);
	return (NULL);
}

static char *get_expansion(const char *var_name, t_minishell *minishell)
{
	char	*expansion;
	t_env_var	*var;

	var = get_var(&minishell->env, var_name);
	while (var)
	{
		if (ft_strcmp(var->name, (char *)var_name) == 0)
			break ;
		var = var->next;
	}
	if (var && var->value)
		expansion = ft_strdup(var->value);
	else
		expansion = ft_strdup("");
	return (expansion);
}

static char *process_dollar(const char *str, int *i, t_minishell *minishell)
{
	int	start;
	char	*var_name;
	char	*expansion;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || ft_isspace(str[*i])) && str[*i] !=  '$')
	{
		(*i)++;
	}
	if ((*i - start) <= 0)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start, (*i) - start);
	if (!var_name)
		return (NULL);
	expansion = get_expansion(var_name, minishell);
	free(var_name);
	return (expansion);
}

static char	*get_next_segment(const char *str, int *i, t_minishell *minishell)
{
	char *segment;

	if (str[*i] == '$')
	{
		segment = process_dollar(str, i, minishell);
		return (segment);
	}
	else
	{
		segment = malloc(sizeof(char) * 2);
		if (!segment)
			return NULL;
		segment[0] = str[*i];
		segment[1] = '\0';
		(*i)++;
		return (segment);
	}
}

char *expand_token_str(const char *str, t_minishell *minishell)
{
	char *result;
	char *tmp;
	char *seg;
	int	i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		seg = get_next_segment(str, &i, minishell);
		if (!seg)
		{
			return(free_str_and_return((char *)result));
		}
		tmp = result;
		result = ft_strjoin(result, seg);
		free(tmp);
		free(seg);
	}
	return (result);
}

t_token_exp *accumulate_token_fragments_expansion(t_token *token, t_minishell *minishell)
{

    t_token_exp *exp_tokens = NULL;
    char *current = ft_strdup("");
    if (!current)
        return (NULL);
    t_fragment *frag = token->fragments;
    while (frag)
    {
        char *expanded = NULL;
        if (frag->quote_type == 1)  /* SINGLE : pas d'expansion */
            expanded = ft_strdup(frag->text);

        else
            expanded = expand_token_str(frag->text, minishell);
        if (!expanded)
        {
            free(current);
            return (NULL);
        }
        if (frag->quote_type == 0)  /* NON cité : on split sur les espaces */
        {
            int ends_with_space = 0;
            int len = strlen(expanded);
            if (len > 0 && expanded[len - 1] == ' ')
                ends_with_space = 1;
            /* ft_split ici doit découper sur ' ' en ignorant les délimiteurs multiples,
               mais ne renvoyer que des chaînes non vides */
            char **parts = ft_split_a(expanded, ' ');
            free(expanded);
            if (!parts)
            {
                free(current);
                return (NULL);
            }
            int count = 0;
            while (parts[count] != NULL)
                count++;
            if (count == 0)
            {
                /* Si la chaîne est uniquement composée d'espaces, rien à concaténer */
                if (ends_with_space)
                {
                    /* Flush le buffer pour marquer la séparation */
                    t_token_exp *new_node = malloc(sizeof(t_token_exp));
                    if (!new_node)
                    {
                        // libérer parts et current…
                        int j = 0;
                        while (parts[j])
                        {
                            free(parts[j]);
                            j++;
                        }
                        free(parts);
                        free(current);
                        return (NULL);
                    }
                    new_node->str = ft_strdup(current);
                    new_node->next = NULL;
                    append_token_exp(&exp_tokens, new_node);
                    free(current);
                    current = ft_strdup("");
                }
            }
            else if (count == 1)
            {
                char *tmp = ft_strjoin(current, parts[0]);
                free(current);
                current = tmp;
                if (ends_with_space)
                {
                    /* Si la partie se terminait par un espace, flush le buffer */
                    t_token_exp *new_node = malloc(sizeof(t_token_exp));
                    if (!new_node)
                    {
                        int j = 0;
                        while (parts[j])
                        {
                            free(parts[j]);
                            j++;
                        }
                        free(parts);
                        free(current);
                        return (NULL);
                    }
                    new_node->str = ft_strdup(current);
                    new_node->next = NULL;
                    append_token_exp(&exp_tokens, new_node);
                    free(current);
                    current = ft_strdup("");
                }
            }
            else
            {
                /* Plusieurs segments */
                /* 1) Concaténer le premier segment au buffer courant */
                {
                    char *tmp = ft_strjoin(current, parts[0]);
                    free(current);
                    current = tmp;
                }
                /* 2) Flush le buffer courant dans un node */
                {
                    t_token_exp *new_node = malloc(sizeof(t_token_exp));
                    if (!new_node)
                    {
                        int j = 0;
                        while (parts[j])
                        {
                            free(parts[j]);
                            j++;
                        }
                        free(parts);
                        free(current);
                        return (NULL);
                    }
                    new_node->str = ft_strdup(current);
                    new_node->next = NULL;
                    append_token_exp(&exp_tokens, new_node);
                }
                /* 3) Pour chaque segment intermédiaire (de 1 à count - 2), créer un node */
                int i = 1;
                while (i < count - 1)
                {
                    t_token_exp *node = malloc(sizeof(t_token_exp));
                    if (!node)
                    {
                        int j = i;
                        while (parts[j])
                        {
                            free(parts[j]);
                            j++;
                        }
                        free(parts);
                        free(current);
                        return (NULL);
                    }
                    node->str = ft_strdup(parts[i]);
                    node->next = NULL;
                    append_token_exp(&exp_tokens, node);
                    i++;
                }
                /* 4) Le dernier segment devient le nouveau buffer */
                free(current);
                current = ft_strdup(parts[count - 1]);
                if (ends_with_space)
                {
                    /* Si la chaîne se terminait par un espace, flush aussi */
                    t_token_exp *node = malloc(sizeof(t_token_exp));
                    if (!node)
                    {
                        int j = 0;
                        while (parts[j])
                        {
                            free(parts[j]);
                            j++;
                        }
                        free(parts);
                        free(current);
                        return (NULL);
                    }
                    node->str = ft_strdup(current);
                    node->next = NULL;
                    append_token_exp(&exp_tokens, node);
                    free(current);
                    current = ft_strdup("");
                }
            }
            int j = 0;
            while (parts[j])
            {
                free(parts[j]);
                j++;
            }
            free(parts);
        }
        else
        {
            /* Fragment cité (SINGLE ou DOUBLE) : concatène simplement */
            char *tmp = ft_strjoin(current, expanded);
            free(expanded);
            free(current);
            current = tmp;
        }
        frag = frag->next;
    }
	if (is_redir(token))
	{
		t_token_exp *new_node = malloc(sizeof(t_token_exp));
        if (!new_node)
        {
            free(current);
            return (NULL);
        }
        new_node->str = "redir";
        new_node->next = NULL;
		append_token_exp(&exp_tokens, new_node);
	}
    else if (current && current[0] != '\0')
    {
        t_token_exp *new_node = malloc(sizeof(t_token_exp));
        if (!new_node)
        {
            free(current);
            return (NULL);
        }
        new_node->str = current;
        new_node->next = NULL;
        append_token_exp(&exp_tokens, new_node);
    }
    else
        free(current);
    return exp_tokens;
}



t_token_exp *create_expanded_tokens(t_token *tokens, t_minishell *minishell)
{
    t_token_exp *result = NULL;
    t_token *cur = tokens;
    while (cur)
    {

			t_token_exp *expanded = accumulate_token_fragments_expansion(cur, minishell);
			if (expanded)
			{
				if (!result)
                	result = expanded;
				else
				{
					t_token_exp *tmp = result;
					while (tmp->next)
                    	tmp = tmp->next;
					tmp->next = expanded;
				}
			}
        cur = cur->next;
    }
    return result;
}

