/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:37:20 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/20 17:56:03 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARRAY_H
# define FT_ARRAY_H

# include "ft_base.h"
# include "ft_free.h"
# include "ft_math.h"
# include "ft_misc.h"
# include "ft_printf.h"
# include "ft_to.h"
# include <stdio.h>

typedef enum e_array_type
{
	ARRAY_INT,
	ARRAY_STRING,
}	t_array_type;

typedef struct s_array
{
	void			*data;
	int				size;
	int				head;
	char			id;
	t_array_type	type;
}					t_array;

int		ft_array_getpos(t_array *arr, int val);
int		ft_array_getval(t_array *arr, int pos, int offset);
int		ft_array_popint(t_array *array, int pos);
int		ft_array_posdist(int current_pos, int dest_pos, int size);
int		ft_array_getmax(t_array *arr);
int		ft_array_getmin(t_array *arr);
void	ft_array_clear(t_array *arr);
void	ft_array_prints(t_array *arr1, t_array *arr2);
t_bool	ft_array_issorted(t_array *arr);
t_array	*ft_array_getsorted(t_array *arr, t_bool replace_by_index);
t_array	*ft_array_cpy(t_array *arr);
t_array	*ft_array_new(char id, int size, t_array_type type);
t_array	*ft_array_pushint(t_array *array, int elt);
t_array	*ft_array_fill(t_array *arr, void *content, t_array_type content_type);

#endif