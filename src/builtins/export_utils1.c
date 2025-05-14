/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:48:19 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 14:44:26 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_identifier(char *str)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = 0;
	while (str[len] && (str[len] != '=' && str[len] != '+'))
		len++;
	res = ft_memalloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (str);
	i = -1;
	while (++i < len)
		res[i] = str[i];
	res[i] = 0;
	return (res);
}

unsigned char	get_operation(char *str)
{
	while (*str && *str != '+' && *str != '=')
		str++;
	if (!*str)
		return (0);
	if (*(str) == '=')
		return (1);
	if (*(str + 1))
	{
		if (*(str) == '+' && *(str + 1) == '=')
			return (2);
	}
	return (3);
}

char	*get_value(char *str)
{
	while (*str && (
			ft_isalnum(*str)
			|| *str == '_'
		))
		str++;
	while (*str && (
			*str == '+'
			|| *str == '='
		))
		str++;
	return (str);
}

t_bool	valid_identifier_name(char *str)
{
	size_t	len;
	size_t	i;

	if (!str)
		return (false);
	if (ft_isalpha(str[0]) == false && str[0] != '_')
		return (false);
	len = ft_strlen(str);
	if (len > 4096 || len < 1)
		return (false);
	i = 0;
	while (++i < len)
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] && str[i + 1] == '='))
			return (true);
		if (ft_isalnum(str[i]) == false && str[i] != '_')
			return (false);
	}
	return (true);
}
