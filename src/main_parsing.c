/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/03 16:46:34 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <strings.h>

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
			parser(token, &minishell);
			free_tokens(token);
			free(line);
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
