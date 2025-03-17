/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:39:07 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/17 16:07:22 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>

typedef unsigned char t_exit;

typedef struct s_command {
	char				*name;
	struct s_command	**value;
}						t_command;

#endif