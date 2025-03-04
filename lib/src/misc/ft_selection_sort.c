/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selection_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:00:28 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/10 11:38:01 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_misc.h"

void	ft_selection_sort(int *tab, int size)
{
	int	i;
	int	j;
	int	min;
	int	tmp;

	i = -1;
	while (++i < size - 1)
	{
		min = i;
		j = i;
		while (++j < size)
		{
			if (tab[j] < tab[min])
				min = j;
		}
		if (min != i)
		{
			tmp = tab[min];
			tab[min] = tab[i];
			tab[i] = tmp;
		}
	}
}
