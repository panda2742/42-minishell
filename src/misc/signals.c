/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:21:20 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/16 16:52:58 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <unistd.h>
#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

void	init_sighandler(void)
{
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_sighandler_heredoc(void)
{
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	check_sigint(t_minishell *mini)
{
	if (g_last_signal == SIG_C || g_last_signal == SIG_HEREDOC)
	{
		mini->last_status = 130;
		g_last_signal = SIG_NO;
	}
}
