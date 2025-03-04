/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_cpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:39:21 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/10 12:40:34 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_array.h"

static void	_cpy_inttab(int *cpytab, int *arrtab, int size);
static void	_cpy_strtab(char **cpytab, char **arrtab);

t_array	*ft_array_cpy(t_array *arr)
{
	t_array	*cpy;
	size_t	bytes;

	cpy = ft_array_new('c', arr->size, arr->type);
	if (!cpy)
		return (NULL);
	cpy->head = arr->head;
	bytes = 0;
	if (arr->type == ARRAY_INT)
		bytes += sizeof(int) * arr->size;
	if (arr->type == ARRAY_STRING)
		bytes += sizeof(char **) * (arr->size + 1);
	cpy->data = malloc(bytes);
	if (!cpy->data)
		return (free(cpy), NULL);
	if (arr->type == ARRAY_INT)
		_cpy_inttab(cpy->data, arr->data, arr->size);
	else if (arr->type == ARRAY_STRING)
		_cpy_strtab(cpy->data, arr->data);
	return (cpy);
}

static void	_cpy_inttab(int *cpytab, int *arrtab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		cpytab[i] = arrtab[i];
}

static void	_cpy_strtab(char **cpytab, char **arrtab)
{
	int		i;
	int		j;
	size_t	len;

	i = -1;
	while (arrtab[++i])
	{
		len = ft_strlen(arrtab[i]);
		cpytab[i] = malloc(sizeof(char *) * (len + 1));
		j = -1;
		while (cpytab[++j])
			cpytab[i][j] = arrtab[i][j];
		cpytab[i][j] = 0;
	}
	cpytab[i] = 0;
}
