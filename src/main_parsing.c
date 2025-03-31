/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/31 14:33:14 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <strings.h>

int	main(void)
{
	char	*line;
	t_token	*token;

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
		if (!lexer_parse(token))
		{
			free(line);
			free_tokens(token);
		}
		else
		{
			
			print_tokens(token);
			free_tokens(token);
		}
		// else
		// {
		// 	parser(token);
		// 	free(line);
		// 	token_clear(&token, del_token);
		// }
		// lst_clear((void **)head, get_next_cmds, del_cmds);
	}
	return (0);
}

// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<
