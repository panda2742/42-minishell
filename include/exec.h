/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:39:07 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/17 19:37:21 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>

typedef unsigned char t_exit;

typedef struct s_command {
	char	*name;
	char	**args;
}			t_command;

typedef t_exit (* command_prototype)(t_command *);

t_exit	exec_command(const char *command_name, const char **command_args);

#endif