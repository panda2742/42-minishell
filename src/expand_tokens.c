#include "minishell.h"

typedef struct s_utils
{
	int i;
	int j;
	int	k;
	int len1;
	int len2;
} t_utils;

static void set_len(t_utils *vars, char *s1, const char *s2)
{
	if (s1)
		vars->len1 = ft_strlen(s1);
	if (s2)
		vars->len2 = ft_strlen(s2);
}

char *str_join_free(char *s1, const char *s2)
{
	char *new;
	t_utils vars;

	ft_memset(&vars, 0, sizeof(t_utils));
	set_len(&vars, s1, s2);
    new = malloc(vars.len1 + vars.len2 + 1);
    if (!new) 
	{ 
		free(s1); 
		return NULL; 
	}
    while (vars.i < vars.len1)
    {
        new[vars.i] = s1[vars.i];
        vars.i++;
    }
    while (vars.j < vars.len2)
    {
        new[vars.i++] = s2[vars.j];
        vars.j++;
    }
    new[vars.i] = '\0';
    free(s1);
    return new;
}

char *expand_fragment(const char *input, int quote, t_env_manager *env)
{
    char *result = ft_strdup("");
    int i = 0;
    while (input[i])
    {
        if (input[i] == '$' && quote != SINGLE) // Si pas entre quotes simples.
        {
            int j = i + 1;
            while (input[j] && ((ft_isalnum(input[j]) || input[j] == '_')))
                j++;
            if (j > i + 1)
            {
                int var_len = j - i - 1;
                char *var_name = malloc(var_len + 1);
                int k = 0;
                while (k < var_len)
                {
                    var_name[k] = input[i + 1 + k];
                    k++;
                }
                var_name[k] = '\0';
                /* Ici on récupère la variable dans notre env manager */
                t_env_var *env_var = get_var(env, var_name);
                char *value;
                if (env_var)
                    value = ft_strdup(env_var->value);
                else
                    value = ft_strdup("");
                free(var_name);
                result = str_join_free(result, value);
                free(value);
                i = j;
                continue;
            }
        }
        {
            char tmp[2];
            tmp[0] = input[i];
            tmp[1] = '\0';
            result = str_join_free(result, tmp);
        }
        i++;
    }
    return result;
}

char *expand_token(t_token *token, t_env_manager *env)
{
    char *result = ft_strdup("");
    if (!result)
        return NULL;
    t_fragment *frag = token->fragments;
    while (frag)
    {
        char *expanded;
        if (frag->quote_type == 1) /* SINGLE quotes : aucun expansion */
            expanded = ft_strdup(frag->text);
        else
            expanded = expand_fragment(frag->text, frag->quote_type, env);
        if (!expanded) { free(result); return NULL; }
        result = str_join_free(result, expanded);
        free(expanded);
        frag = frag->next;
    }
    return result;
}
void expand_all_tokens(t_token *tokens, t_env_manager *env)
{
    t_token *t = tokens;
    while (t)
    {
        char *exp = expand_token(t, env);
        printf("Expanded token: %s\n", exp); // Exemple de sortie : a b a      b     a b
        free(exp);
        t = t->next;
    }
}

static t_token *create_new_token_from_word(const char *word)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = WORD;
    token->index = 0;
    token->fragments = malloc(sizeof(t_fragment));
    if (!token->fragments)
    {
        free(token);
        return (NULL);
    }
    token->fragments->text = ft_strdup(word);
    token->fragments->quote_type = NONE;
    token->fragments->next = NULL;
    token->next = NULL;
    return (token);
}

static void process_unquoted_fragment(const char *expanded, char **current, t_token **new_head, t_token **new_last)
{
    int i = 0;
    while (expanded[i])
    {
        if (expanded[i] == ' ' || expanded[i] == '\t' || expanded[i] == '\n')
        {
            /* Si current n'est pas vide, on le finalise */
            if ((*current)[0] != '\0')
            {
                t_token *nt = create_new_token_from_word(*current);
                if (!*new_head)
                {
                    *new_head = nt;
                    *new_last = nt;
                }
                else
                {
                    (*new_last)->next = nt;
                    *new_last = nt;
                }
                free(*current);
                *current = ft_strdup("");
            }
            /* Sauter tous les séparateurs */
            while (expanded[i] && (expanded[i] == ' ' || expanded[i] == '\t' || expanded[i] == '\n'))
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
    t_token *new_head = NULL;
    t_token *new_last = NULL;
    char *current = ft_strdup("");
    t_fragment *frag = token->fragments;
    while (frag)
    {
        char *expanded;
        if (frag->quote_type == NONE)
        {
            expanded = expand_fragment(frag->text, frag->quote_type, env);
            if (!expanded) { free(current); return (NULL); }
            process_unquoted_fragment(expanded, &current, &new_head, &new_last);
            free(expanded);
        }
        else
        {
            /* Pour DOUBLE quotes, on effectue quand même l'expansion,
               et pour SINGLE, on fait un strdup */
            if (frag->quote_type == DOUBLE)
                expanded = expand_fragment(frag->text, frag->quote_type, env);
            else
                expanded = ft_strdup(frag->text);
            if (!expanded) { free(current); return (NULL); }
            /* Simple concaténation pour les fragments cités */
            current = str_join_free(current, expanded);
            free(expanded);
        }
        frag = frag->next;
    }
    t_token *nt = create_new_token_from_word(current);
    if (!nt) { free(current); return (new_head); }
    if (!new_head)
        new_head = nt;
    else
        new_last->next = nt;
    free(current);
    return (new_head);
}
