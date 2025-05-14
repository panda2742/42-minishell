/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token_to_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:07:06 by abonifac          #+#    #+#             */
/*   Updated: 2025/04/23 14:49:02 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*
//  * Just used to build the raw string from the token list.
// */

// char	*join_tokens_to_string(t_token *tokens)
// {
// 	char	*result;
// 	t_token	*tmp;

// 	result = ft_strdup("");
// 	tmp = tokens;
// 	if (!result)
// 		return (NULL);
// 	while (tmp)
// 	{
// 		if (tmp->fragments && tmp->fragments->text)
// 			result = str_join_free(result, tmp->fragments->text);
// 		if (tmp->next)
// 			result = str_join_free(result, " ");
// 		tmp = tmp->next;
// 	}
// 	return (result);
// }
