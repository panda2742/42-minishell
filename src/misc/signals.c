/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:21:20 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/14 12:16:25 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <unistd.h>
#include "minishell.h"

int last_signal = 0;

/*
	sigaction struct:
		struct sigaction {
			void (*sa_handler)(int);
			sigset_t sa_mask;
			int sa_flags;
		};
		- sa_handler: pointeur sur la fonction de gestion du signal
		- sigemptyset: initialise le masque de signaux a bloquer,
			en gros on ne bloque aucun signal
		- sa_flags: flags pour la gestion du signal,
			SA_RESTART pour redemarrer les appels systeme interrompus
		- sigaction: Quand SIGINT arrive,
			appelle sigint_handler et applique les options (sa_mask, sa_flags)
		- signal: ignore SIGQUIT
*/

void sigint_handler(int sig)
{
	(void)sig;
	rl_redisplay();
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	last_signal = 3;
}

/* on installe dans la boucle, avant chaque readline */
void init_sighandler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void sigint_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	last_signal = 5;
	close(STDIN_FILENO);
}

/* on installe dans la boucle, avant chaque readline */
void init_sigheredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
