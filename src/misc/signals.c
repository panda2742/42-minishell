/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:21:20 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:21:50 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

void	sigint_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

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
void	set_sig_action(void)
{
	struct sigaction	act;

	act.sa_handler = &sigint_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}
