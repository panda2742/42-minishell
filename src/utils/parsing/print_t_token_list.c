/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_t_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:30:13 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 16:01:36 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Print each chunk between pipes 
*/
void	print_token_list(t_token_list *list)
{
	t_token_list	*tmp_list;
	t_token			*tmp_token;

	tmp_list = list;
	while (tmp_list)
	{
		tmp_token = tmp_list->tokens;
		ft_printf("Token list: ");
		while (tmp_token)
		{
			printf("%s/", tmp_token->text);
			tmp_token = tmp_token->next;
		}
		printf("\n");
		tmp_list = tmp_list->next;
	}
}
