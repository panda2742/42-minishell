/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:09:25 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/18 14:40:20 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_prompt(void)
{
	const char	*cwd = getcwd(NULL, 0);

	printf(GREEN "%s/ " RESET, ft_strrchr(cwd, '/') + 1);
	free((char *)cwd);
	printf(BLUE "minishell $" RESET);
}
