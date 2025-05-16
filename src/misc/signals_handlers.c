/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:07:18 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/16 15:58:24 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_signal = SIG_C;
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "^C", 3);
	g_last_signal = SIG_HEREDOC;
	close(STDIN_FILENO);
}
