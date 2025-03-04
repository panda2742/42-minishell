/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_prints.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:13:37 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/13 09:40:18 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

static void	_ft_array_print_single(t_array *arr, int i);
static void	_display_int(t_array *arr, int i);
static void	_display_str(t_array *arr, int i);

void	ft_array_prints(t_array *arr1, t_array *arr2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < arr1->size || (arr2 && j < arr2->size))
	{
		if (i < arr1->size)
			_ft_array_print_single(arr1, i);
		else
			ft_printf(" ");
		ft_printf("  ", i, j);
		if (arr2 && j < arr2->size)
			_ft_array_print_single(arr2, j);
		ft_printf("\n");
		i++;
		j++;
	}
	if (arr2)
		ft_printf("_  _\n");
	ft_printf(GREEN "%c", arr1->id);
	if (arr2)
		ft_printf("  %c", arr2->id);
	ft_printf(RESET "\n");
}

static void	_ft_array_print_single(t_array *arr, int i)
{
	if (arr->type == ARRAY_INT)
		_display_int(arr, i);
	else if (arr->type == ARRAY_STRING)
		_display_str(arr, i);
}

static void	_display_int(t_array *arr, int i)
{
	if (i == arr->head)
		ft_printf(RED "%d" RESET, ((int *)arr->data)[i]);
	else
		ft_printf(BLUE "%d" RESET, ((int *)arr->data)[i]);
}

static void	_display_str(t_array *arr, int i)
{
	if (i == arr->head)
		ft_printf(RED "%s" RESET, ((char **)arr->data)[i]);
	else
		ft_printf(BLUE "%s" RESET, ((char **)arr->data)[i]);
}
