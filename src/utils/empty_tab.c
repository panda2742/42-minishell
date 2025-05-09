/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:29:49 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/09 14:37:01 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*empty_tab(void)
{
	static void	*tab[1] = {NULL};

	return (tab);
}

char	**empty_paths(void)
{
	static char	*tab[5] = {
		"/usr/local/sbin",
		"/usr/local/bin",
		"/usr/bin",
		"/usr/sbin",
		"/snap/bin"
	};

	return (tab);
}
