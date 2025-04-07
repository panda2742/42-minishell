/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/07 21:10:39 by abonifac         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*token;
	t_minishell	minishell;
	(void)env;
	(void)argc;
	(void)argv;

	if (create_env(env, &minishell.env) == NULL)
		return (EXIT_FAILURE);

	token = NULL;
	// char	**map;
	while (1)
	{
		set_sig_action();
		line = readline("minishell$ ");
		// Gere la sortie propre avec CTRL D
		if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		token = ft_input(line);
		if (token == NULL)
		{
			free(line);
			free_tokens(token);
		}
		// t_env_var *test = get_var(&minishell.env, "USER");
		// printf("%s %s\n", test->name, test->value);
		else if (!lexer_parse(token))
		{
			free_tokens(token);
			free(line);
		}
		else
		{
			print_tokens(token);
			t_token_exp *expanded_tokens;
			expanded_tokens = create_expanded_tokens(token, &minishell);
			print_token_exp(expanded_tokens);
			char *join_expanded_tokens = join_token_exp(expanded_tokens);
			ft_printf("Token expandeds:%s\n",join_expanded_tokens);
			free(join_expanded_tokens);
			// parser(token, &minishell);
			free_expandeds(expanded_tokens);
			free_tokens(token);
			// free(line);
		}
		// else
		// {
		// 	parser(token);
			// free(line);
		// free_tokens(token);
		// }
		// lst_clear((void **)head, get_next_cmds, del_cmds);
	}
	return (0);
}

// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<
