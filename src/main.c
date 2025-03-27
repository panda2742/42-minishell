/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/27 15:21:34 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**test_parsing(char *s)
{
	char	**mapped;
	int	i;
	
	i = 0;
	mapped = ft_split(s, " ");
	while (mapped[i])
	{
		ft_printf("%s\n", mapped[i]);
		i++;
	}
	return (mapped);
}

#include <strings.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>



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
			token_clear(&token, del_token);
		}
		else
		{	
			parser(token);
			free(line);
			token_clear(&token, del_token);
		}
		//lst_clear((void **)head, get_next_cmds, del_cmds);

	}
	return (0);
}


// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<

