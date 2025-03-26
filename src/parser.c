

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
	int	expand;
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
	t_redir 		*redir;
	struct s_cmds	*next;
} t_cmds;

#include "minishell.h"



void create_cmds(t_token *head_token, t_token *end, t_cmds **head);

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

	// permet de retourner en arriere pour lire du debut jusqu au | ou NULL
	t_token *start = head;
	// on parcourt la liste
	while (tmp != NULL)
	{
		// on cree une commande entre start et end
		if (tmp->type == PIPE || tmp->next == NULL)
		{
			
			create_cmds(start, tmp, &head_cmd);
			start = tmp->next;
		}
		tmp = tmp->next;
	}

	return 0;
}

void create_word(char *value, int expand, t_word **head_w)
{
	t_word *new;
	t_word *tmp;

	tmp = *head_w;
	
	new = malloc(sizeof(t_word));
	if (!new)
		return ; //
	new->word = ft_strdup(value); // value direct ou copier?
	if (!new->word)
	{
		free(new);
		return ; //
	}
	new->expand = expand; // $ ou pas 
	new->next = NULL;
	
	if (*head_w == NULL)
	{
		*head_w = new;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	// ft_printf("Create word: %s expand %i\n", new->word, new->expand);
}

void create_redir(t_redir **head_r, t_token *head)
{
	t_redir *new;
	t_redir *tmp;

	if (!head->next || !head)
		return ;
	tmp = *head_r;
	
	new = malloc(sizeof(t_redir));
	if (!new)
	{
		return ; //
	}
	new->type = head->type; // redir type
	new->expand = head->next->expand; // $ ou pas 
	// on dup ce qu'il y a apres la redir
	new->filename = ft_strdup(head->next->value);
	if (!new->filename)
	{
		free(new);
		return ; //
	}
	if (!new->filename)
		return ; //
	new->next = NULL;
	
	if (*head_r == NULL)
	{
		*head_r = new;
	}
	else
	{
		tmp = *head_r;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	// ft_printf("Create redir: type %i | value: %s | expand %i\n", new->type, new->filename, new->expand);
}



void create_cmds(t_token *head_token, t_token *end, t_cmds **head)
{
	t_cmds *new;
	t_cmds *tmp;
	t_word *head_w = NULL;
	t_redir *head_r = NULL;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return ; //

	while (head_token != end->next)
	{
		if (head_token->type == WORD)
		{
			create_word(head_token->value, head_token->expand, &head_w);
		}
		else if (is_redir(head_token))
		{
			create_redir(&head_r, head_token);
			head_token = head_token->next;
		}
		head_token = head_token->next;
	}
	// create_word(head_token->value, head_token->expand, &head_w);

	new->words = head_w;
	new->redir = head_r;
	new->next = NULL;

	
	// initialise head
	if (!*head)
		*head = new;
	// parcourt la liste jusqu au dernier element, ajoute a la fin
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	while (head_w != NULL)
	{
		ft_printf("Create word: %s expand %i\n", head_w->word, head_w->expand);
		head_w = head_w->next;
	}
	while (head_r != NULL)
	{
		ft_printf("Create redir: type %s | value: %s | expand %i\n", get_token_type_str(head_r->type), head_r->filename, head_r->expand);
		head_r = head_r->next;
	}
}
