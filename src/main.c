/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/17 19:26:06 by abonifac         ###   ########.fr       */
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

void	del_token(void *content)
{
	t_token *token;
	token = (t_token *)content;
	if (token->value)
		free(token->value);
	free(token);
}

void	token_clear(t_token **lst, void (*del)(void *))
{
	t_token *tmp;
	
	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

#include <signal.h>
#include <strings.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("SIGINT\n");
	}
}

void set_sig_action(void)
{
	struct sigaction act;
	
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}


int	main(void)
{
	char	*line;
	t_token	*token;
	
	token = NULL;
	// char	**map;
	
	set_sig_action();
	while (1)
	{
		line = readline(BLUE "minishell$ " RESET);
		// Gere la sortie propre avec CTRL D
		if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		
		token = ft_input(line);

		t_token *tmp = token;
		while (tmp != NULL)
		{
			ft_printf("Type is: %d, value is %s, index is %i, expand %i\n", tmp->type, tmp->value, tmp->index, tmp->expand);
			tmp = tmp->next;
		}
		// map = test_parsing(line);
		free(line);
		token_clear(&token, del_token);
	}
	return (0);
}


// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<

