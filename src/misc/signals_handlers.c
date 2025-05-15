/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:07:18 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/15 16:39:30 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_display_nl(char c);

void	sigint_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_signal = SIG_C;
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	g_last_signal = SIG_HEREDOC;
	close(STDIN_FILENO);
}
