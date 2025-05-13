/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_random_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:41:39 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/13 14:41:43 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_return_crash(int *urandom_fd)
{
	close(*urandom_fd);
	return (ft_strdup("omg_it_crashed"));
}

static char	*_close_urand_return_res(int *urandom_fd, char *res)
{
	close(*urandom_fd);
	return (res);
}

int	_while_buffer(char *buffer, t_utils *utils, char *res, uint8_t n)
{
	while (buffer[utils->j])
	{
		if (ft_isalnum(buffer[utils->j]))
			res[utils->i++] = buffer[utils->j];
		utils->j++;
		if (utils->i == n)
			return (0);
	}
	return (1);
}
/*
 * read_bytes = utils.k
*/

char	*get_random_chars(uint8_t n)
{
	char	*res;
	int		urandom_fd;
	char	buffer[4096];
	t_utils	utils;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd == -1)
		return (ft_strdup("omg_it_crashed"));
	res = ft_memalloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (_return_crash(&urandom_fd));
	ft_memset(res, '?', n);
	res[n] = 0;
	utils.i = 0;
	while (1)
	{
		utils.k = read(urandom_fd, buffer, 4096);
		if (utils.k <= 0)
			break ;
		utils.j = 0;
		if (_while_buffer(buffer, &utils, res, n) == 0)
			break ;
	}
	return (_close_urand_return_res(&urandom_fd, res));
}
