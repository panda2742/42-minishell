
#include <signal.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

/*
	Handle CTRL C 
*/
void	sigint_handler(int signal)
{
	// void juste pour utiliser signal pour les flags
	(void)signal;
	write(1, "\n", 1);
	// remplace la ligne actuelle par "", 1 pour supp l historique, 0 conserver
	rl_replace_line("", 0);
	// informe realine que l on passe a une nouvelle ligne
	rl_on_new_line();
	// rappel le prompt
	rl_redisplay();
}


void set_sig_action(void)
{
	struct sigaction act;
	
	act.sa_handler = &sigint_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	
}