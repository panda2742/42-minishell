

// Si je commence par un pipe ➔ erreur
// Si je trouve une redirection ➔ il faut que je trouve un mot juste après
// Deux pipes qui se suivent ➔ erreur
// Si je termine par un pipe ➔ erreur
// Les quotes fermées ➔ déjà gérées dans le lexer normalement, donc le parser est clean là-dessus


// Tu pars du début de la liste des tokens
// Tant que ce n’est pas un pipe ou la fin :
// Si c’est un WORD et que t’as pas de commande ➔ c’est ta commande
// Si c’est un WORD et que la commande est là ➔ c’est un argument
// Si c’est une redirection ➔ tu vérifies qu’il y a un WORD derrière ➔ sinon erreur
// Si tu tombes sur un pipe ➔ tu vérifies que t’as bien eu une commande avant ➔ tu passes à la suite
// Si la liste se termine ➔ tu vérifies que la dernière commande était valide

typedef struct s_token {
	t_token_type type;
	char *value;
	int expand;
	int	index;
	struct s_token *next;
} t_token;



typedef struct s_redir
{
	int type;
	char *filename;
} t_redir;

typedef struct s_cmds
{
	char			**str;
	t_redir 		*redir;
	struct s_cmds	*next;
} t_cmds;

#include "minishell.h"

int parser(t_token *head)
{
	t_token *tmp = head;

	while (tmp->type != PIPE || tmp != NULL)
	{
		tmp = tmp->next;
	}
	return 0;
}

void create_cmds(t_cmds **head, int n)
{
	t_cmds *new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return ; //
	new->str = malloc(n);
	
	
	if (head == NULL)
	{
		head = new;
	}

}