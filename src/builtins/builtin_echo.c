/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:14 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/09 18:22:53 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_only_n(char *str);
static t_bool	handle_echo_option(char **av, int argc, int *i);

t_exit	builtin_echo(t_excmd *c)
{
	int		i;
	char	**av;
	t_bool	option;

	i = 0;
	av = c->argv;
	av++;
	c->argc--;
	if (c->argc == 0)
	{
		ft_printf("\n");
		return (EXIT_SUCCESS);
	}
	option = handle_echo_option(av, c->argc, &i);
	while (i < c->argc && av[i])
	{
		ft_printf("%s", av[i]);
		if (i < c->argc - 1)
			ft_printf(" ");
		i++;
	}
	if (option == false)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}

static int	check_only_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] == 'n')
	{
		i++;
	}
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

static t_bool	handle_echo_option(char **av, int argc, int *i)
{
	t_bool	option;

	option = false;
	if (ft_strlen(av[0]) > 1)
	{
		while (*i < argc && check_only_n(av[*i]))
		{
			(*i)++;
			option = true;
			if (*i >= argc)
				break ;
		}
		return (option);
	}
	return (option);
}
