

// Si je commence par un pipe : erreur
// Si je trouve une redirection : il faut que je trouve un mot juste après
// Deux pipes qui se suivent : erreur
// Si je termine par un pipe : erreur
// Les quotes fermées : déjà gérées dans le lexer normalement, donc le parser est clean là-dessus


// Tu pars du début de la liste des tokens
// Tant que ce n’est pas un pipe ou la fin :
// Si c’est un WORD et que t’as pas de commande : c’est ta commande
// Si c’est un WORD et que la commande est là : c’est un argument
// Si c’est une redirection : tu vérifies qu’il y a un WORD derrière : sinon erreur
// Si tu tombes sur un pipe : tu vérifies que t’as bien eu une commande avant : tu passes à la suite
// Si la liste se termine : tu vérifies que la dernière commande était valide

// typedef struct s_token {
// 	t_token_type type;
// 	char *value;
// 	int expand;
// 	int	index;
// 	struct s_token *next;
// } t_token;



typedef struct s_redir
{
	int type;
	char *filename;
	struct s_redir *next;
} t_redir;

typedef struct s_word
{
	int expand;
	char *word;
	struct s_word *next;
} t_word;

typedef struct s_cmds
{
	t_word			*words;
	t_redir 		**redir;
	struct s_cmds	*next;
} t_cmds;

#include "minishell.h"
void create_cmds(t_token *head_token, t_cmds **head, int n);

int parser(t_token *head)
{
	t_token *tmp = head;
	t_cmds *head_cmd = NULL;

	// si on fait entrer renvoie le prompt
	if (tmp == NULL)
		return 0; //
	if (tmp->type == PIPE)
	{
		ft_printf("Error: syntax error near unexpected token `|'\n"); //
		return 0; //
	}

	while (tmp != NULL)
	{
		t_token *start = head;
		if (tmp->type == PIPE || tmp->next == NULL)
		{
			
			create_cmds(start, &head_cmd, 4);
			start = tmp->next;
		}
		tmp = tmp->next;
	}
	return 0;
}

void create_word(char *value, int expand, t_word **head)
{
	t_word *new;
	t_word *tmp;

	tmp = *head;
	
	new = malloc(sizeof(t_word));
	if (!new)
		return ; //
	new->word = value; // value direct ou copier?
	new->expand = expand; // $ ou pas 
	new->next = NULL;
	
	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		new->next = tmp;
		*head = new;
	}



}
void create_cmds(t_token *head_token, t_cmds **head, int n)
{
	t_cmds *new;
	t_cmds *temp;
	t_word *head_w = NULL;

	(void)(head_token);
	int x = 4;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return ; //
	while (head_token != PIPE && head_token != NULL)
	{
		if (head_token->type == WORD)
		{
			create_word(head_token->value, head_token->expand, &head_w);
		}
	}
	new->words = malloc(sizeof(t_word) * n);
	new->redir = malloc(x);
	new->next = NULL;

	
	// initialise head
	if (!*head)
		*head = new;
	// parcourt la liste jusqu au dernier element, ajoute a la fin
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		new = temp->next;
	}

}