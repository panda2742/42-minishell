/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:07:18 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/15 12:11:39 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_last_signal != SIG_HEREDOC)
		write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_signal = SIG_C;
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	init_sighandler();
	g_last_signal = SIG_HEREDOC;
	close(STDIN_FILENO);
}
