/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:47:18 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/09 20:10:12 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Check if the environment was created successfully
 * If not, print an error message and exit
 * Malloc secured
*/

void	create_env_or_exit_if_env_error(char **env, t_minishell *minishell,
	int argc, char **argv)
{
	t_env_var **env_var;

	minishell->argc = argc;
	minishell->argv = argv;
	minishell->prompt_theme = -1;
	minishell->last_status = EXIT_SUCCESS;
	if (env == NULL)
	{
		puterr(ft_sprintf(
			": error: Environment creation memory allocation failure\n"),
			false);
		exit (EXIT_FAILURE);
	}
	env_var = create_env(env, &minishell->env);
	if (env_var == NULL)
	{
		puterr(ft_sprintf(
		": error: Environment creation memory allocation failure\n"),
			false);
		exit (EXIT_FAILURE);
	}
}