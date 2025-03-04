/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_posdist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:25:10 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/12 12:05:38 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

int	ft_array_posdist(int current_pos, int dest_pos, int size)
{
	int	dist_f;
	int	dist_b;

	if (dest_pos == current_pos)
		return (0);
	if (current_pos < dest_pos)
	{
		dist_f = dest_pos - current_pos;
		dist_b = -(current_pos + (size - 1 - dest_pos) + 1);
	}
	else
	{
		dist_f = (size - 1 - current_pos) + dest_pos + 1;
		dist_b = -(current_pos - dest_pos);
	}
	if ((int)ft_abs(dist_b) >= dist_f)
		return (dist_f);
	return (dist_b);
}
