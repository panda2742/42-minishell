/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/08 14:47:01 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <strings.h>

void print_token_exp(t_token_exp *tokens)
{
    while (tokens)
    {
        printf("Expanded token: '%s'\n", tokens->str);
        tokens = tokens->next;
    }
}

char *join_token_exp(t_token_exp *tokens)
{
    char *result;
    char *tmp;
    t_token_exp *cur;

    result = ft_strdup(""); /* On initialise result avec une chaîne vide */
    if (!result)
        return (NULL);
    cur = tokens;
    while (cur)
    {
        tmp = ft_strjoin(result, cur->str);
        free(result);
        result = tmp;
        if (cur->next)
        {
            tmp = ft_strjoin(result, " ");
            free(result);
            result = tmp;
        }
        cur = cur->next;
    }
    return result;
}

void	free_expandeds(t_token_exp *tokens)
{
	t_token_exp	*tmp;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->str);
		free(tokens);
		tokens = tmp;
	}
}

char *join_tokens_to_string(t_token *tokens)
{
    char *result = ft_strdup("");
    t_token *tmp = tokens;
    if (!result)
        return (NULL);
    while (tmp)
    {
        if (tmp->fragments && tmp->fragments->text)
            result = str_join_free(result, tmp->fragments->text);
        if (tmp->next)
            result = str_join_free(result, " ");
        tmp = tmp->next;
    }
    return (result);
}



#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    char            *line;
    t_token         *token;
    t_token         *new_tokens;  // Pour stocker le résultat du word splitting
    t_env_manager   minishell;    // Gestionnaire d'environnement (alloué et initialisé via create_env)

    (void)argc;
    (void)argv;
    if (create_env(env, &minishell) == NULL)
    {
        ft_printf("Error initializing environment\n");
        return (EXIT_FAILURE);
    }
    while (1)
    {
        set_sig_action();
        line = readline("minishell$ ");
        if (!line)  // CTRL+D
        {
            ft_printf("exit\n");
            break;
        }
        token = ft_input(line);
        if (token == NULL)
        {
            free(line);
            continue;
        }
        if (!lexer_parse(token))
        {
            free_tokens(token);
            free(line);
            continue;
        }
        // Ici, on a déjà la phase d'expansion dans chaque token, et on affiche le résultat d'expansion
        // On applique ensuite le word splitting sur chaque token. 
        // Ici, word_split_token() reçoit un token et son environnement, et retourne une nouvelle chaîne de tokens.
        t_token *tmp = token;
        new_tokens = NULL;
        t_token *last_new = NULL;
        while (tmp)
        {
            t_token *split_token = word_split_token(tmp, &minishell);
            if (split_token)
            {
                // Concatène la chaîne de tokens obtenue via le word splitting
                if (!new_tokens)
                {
                    new_tokens = split_token;
                    last_new = new_tokens;
                }
                else
                {
                    while (last_new->next)
                        last_new = last_new->next;
                    last_new->next = split_token;
                }
            }
            tmp = tmp->next;
        }
        // On peut afficher la nouvelle liste de tokens après word splitting
		char *final_cmd = join_tokens_to_string(new_tokens);
		ft_printf("Final command line: %s\n", final_cmd);
		print_tokens(token);
        print_tokens(new_tokens);
        free_tokens(token);
        free_tokens(new_tokens);
        free(line);
    }
    // free_env_manager(&minishell);
    return (0);
}



// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<
