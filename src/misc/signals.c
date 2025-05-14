/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:21:20 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 14:13:50 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <unistd.h>
#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	rl_redisplay();
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_last_signal = 3;
}

/* We set it before readline to handle the signals main*/
void	init_sighandler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	g_last_signal = 5;
	close(STDIN_FILENO);
}

/* We set it before readline to handle the signals fake heredoc*/
void	init_sigheredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	check_sigint(t_minishell *mini)
{
	if (g_last_signal == 3)
	{
		mini->last_status = 130;
		g_last_signal = 0;
	}
}
