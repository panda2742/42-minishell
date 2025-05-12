/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_random_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:41:39 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/12 17:01:49 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_random_chars(uint8_t n)
{
	char	*res;
	int		urandom_fd;
	ssize_t	read_bytes;
	char	buffer[4096];
	size_t	i;
	size_t	j;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd == -1)
		return (ft_strdup("omg_it_crashed"));
	res = ft_memalloc(sizeof(char) * (n + 1));
	if (res == NULL)
	{
		close(urandom_fd);
		return (ft_strdup("omg_it_crashed"));
	}
	ft_memset(res, '?', n);
	res[n] = 0;
	i = 0;
	while (1)
	{
		read_bytes = read(urandom_fd, buffer, 4096);
		if (read_bytes == -1)
		{
			close(urandom_fd);
			return (res);
		}
		if (read_bytes == 0)
		{
			close(urandom_fd);
			return (res);
		}
		j = 0;
		while (buffer[j])
		{
			if (ft_isalnum(buffer[j]))
				res[i++] = buffer[j];
			j++;
			if (i == n)
			{
				close(urandom_fd);
				return (res);
			}
		}
	}
	close(urandom_fd);
	return (res);
}
