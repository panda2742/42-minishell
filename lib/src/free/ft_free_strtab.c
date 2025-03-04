/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:13:55 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/10 12:23:49 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_free.h"

void	ft_free_strtab(char **strtab)
{
	int	i;

	i = -1;
	while (strtab[++i])
		ft_free_str(strtab[i]);
	free(strtab);
	strtab = NULL;
}
