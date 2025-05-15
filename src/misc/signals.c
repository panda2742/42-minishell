/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:21:20 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/15 12:03:46 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <unistd.h>
#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;


/* We set it before readline to handle the signals main*/
void	init_sighandler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/* We set it before readline to handle the signals fake heredoc*/
void	init_sighandler_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	check_sigint(t_minishell *mini)
{
	if (g_last_signal == SIG_C)
	{
		mini->last_status = 130;
		g_last_signal = SIG_NO;
	}
}
