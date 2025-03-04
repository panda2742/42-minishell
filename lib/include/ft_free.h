/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:58:34 by ehosta            #+#    #+#             */
/*   Updated: 2025/02/10 12:17:21 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FREE_H
# define FT_FREE_H

# include <stdlib.h>

void	ft_free_inttab(int *tab);
void	ft_free_str(char *str);
void	ft_free_strtab(char **strtab);

#endif