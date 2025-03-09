/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/09 20:15:48 by abonifac         ###   ########.fr       */
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

void	*del(void *list)
{
	free(list);
}

int	main(void)
{
	char	*line;
	t_token	*token;
	token = NULL;
	// char	**map;
	
	while (1)
	{
		ft_printf(BLUE "minishell$ " RESET);
		line = get_next_line(0);
		token = ft_input(line);
		while (token != NULL)
		{
			ft_printf("Type is: %d, value is %s\n", token->type, token->value);
			token = token->next;
		}
		// map = test_parsing(line);
		free(line);
	}
	ft_lstclear(&token, del(token));
	return (0);
}
