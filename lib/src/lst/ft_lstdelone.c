/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:39:38 by ehosta            #+#    #+#             */
/*   Updated: 2024/11/13 11:39:38 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_lst.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del && lst)
	{
		del(lst->content);
		free(lst);
	}
}
