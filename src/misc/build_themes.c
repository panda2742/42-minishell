/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_themes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:39:42 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/15 11:31:14 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_theme0(const char *user, const char *path)
{
	char	*res;

	res = ft_sprintf(
			"@%s %s %s > ",
			user, path, PROJECT_NAME);
	return (res);
}

char	*build_theme1(int last_status, const char *user, const char *path)
{
	char	*res;

	res = ft_sprintf(
			B_WHITE "%d" RESET " × "
			B_MAGENTA "%s" RESET ":: "
			B_BLUE "%s" RESET " @ "
			B_CYAN "%s" RESET " "
			B_MAGENTA ">" RESET " ",
			last_status, PROJECT_NAME, user, path);
	return (res);
}

char	*build_theme2(int last_status, const char *path)
{
	char	*res;

	res = ft_sprintf(
			B_MAGENTA "%d" RESET " - "
			U_GREEN "%s" RESET " "
			WHITE "$" RESET " ",
			last_status, path);
	return (res);
}
