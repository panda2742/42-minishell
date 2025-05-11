/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_themes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:39:42 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/11 13:47:26 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_theme0(int last_status, const char *user, const char *path)
{
	char	*res;

	res = ft_sprintf(
			"\001%s\002%d\001%s\002 × "
			"\001%s\002%s\001%s\002:: "
			"\001%s\002%s\001%s\002 @ "
			"\001%s\002%s\001%s\002 "
			"\001%s\002>\001%s\002 ",
			B_WHITE, last_status, RESET,
			B_MAGENTA, PROJECT_NAME, RESET,
			B_BLUE, user, RESET,
			B_CYAN, path, RESET,
			B_MAGENTA, RESET
			);
	return (res);
}

char	*build_theme1(int last_status, const char *path)
{
	char	*res;

	res = ft_sprintf(
			"\001%s\002%d\001%s\002 - "
			"\001%s\002%s\001%s\002 "
			"\001%s\002$\001%s\002 ",
			B_MAGENTA, last_status, RESET,
			U_GREEN, path, RESET,
			WHITE, RESET
			);
	return (res);
}
