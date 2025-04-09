/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/09 22:11:01 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <strings.h>

char	*join_tokens_to_string(t_token *tokens)
{
	char	*result;
	t_token	*tmp;

	result = ft_strdup("");
	tmp = tokens;
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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*token;
	t_token	*tmp;
	t_token	*last_new;
	t_token	*split_token;
	char	*final_cmd;

	t_token *new_tokens;     // Pour stocker le resultat du word splitting
	t_env_manager minishell;
		// Gestionnaire d'environnement (alloue et initialise via create_env)
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
		if (!line || !ft_strcmp(line, "exit")) // CTRL+D || "exit"
		{
			ft_printf("exit\n");
			break ;
		}
		token = ft_input(line);
		if (token == NULL)
		{
			free(line);
			continue ;
		}
		if (!lexer_parse(token))
		{
			free_tokens(token);
			free(line);
			continue ;
		}
		/*Ici, on a dejà la phase d'expansion dans chaque token,
			et on affiche le resultat d'expansion
		// On applique ensuite le word splitting sur chaque token.
		// Ici, word_split_token() reçoit un token et son environnement,
			et retourne une nouvelle chaine de tokens */
		tmp = token;
		new_tokens = NULL;
		last_new = NULL;
		while (tmp)
		{
			split_token = word_split_token(tmp, &minishell);
			if (split_token)
			{
				// Concatene la chaine de tokens obtenue via le word splitting
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
		final_cmd = join_tokens_to_string(new_tokens);
		// print_tokens(token);
		ft_printf("Final command line: %s\n", final_cmd);
		print_tokens(new_tokens);
		free_tokens(token);
		free_tokens(new_tokens);
		free(line);
		free(final_cmd);
	}
	// free_env_manager(&minishell);
	return (0);
}

// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<
