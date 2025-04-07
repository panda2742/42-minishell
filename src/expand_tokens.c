

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

char *expand_token_str(const char *str, t_minishell *minishell)
{
    char    *result;
    char    *tmp;
    int     i = 0;
    int     start, var_len;
    char    *var_name;
    t_env_var *var;
    const char *value;

    result = ft_strdup("");
    if (!result)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '$')
        {
            i++; /* saute le '$' */
            start = i;
            while (str[i] && (ft_isalnum(str[i]) || ft_isspace(str[i])))
                i++;
            var_len = i - start;
            if (var_len <= 0)
            {
                tmp = ft_strjoin(result, "$");
                free(result);
                result = tmp;
                continue;
            }
            var_name = malloc(var_len + 1);
            if (!var_name)
            {
                free(result);
                return (NULL);
            }
            strncpy(var_name, str + start, var_len);
            var_name[var_len] = '\0';
            var = get_var(&minishell->env, var_name);
            while (var)
            {
                if (strcmp(var->name, var_name) == 0)
                    break;
                var = var->next;
            }
            free(var_name);
            value = "";
            if (var && var->value)
                value = var->value;
            tmp = ft_strjoin(result, value);
            free(result);
            result = tmp;
        }
        else
        {
			tmp = result;
            result = append_char(str[i], result);
            free(tmp);
            i++;
        }
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
    if (current && current[0] != '\0')
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
        /* On ajoute la liste obtenue pour ce token à la fin du résultat global.
           Ici, on peut imaginer une fonction append_token_exp_list qui concatène deux listes. */
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

