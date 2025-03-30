

// Si je commence par un pipe : erreur
// Si je trouve une redirection : il faut que je trouve un mot juste après
// Deux pipes qui se suivent : erreur
// Si je termine par un pipe : erreur
// Les quotes fermées : déjà gérées dans le lexer normalement,
// donc le parser est clean là-dessus

// Tu pars du début de la liste des tokens
// Tant que ce n’est pas un pipe ou la fin :
// Si c’est un WORD et que t’as pas de commande : c’est ta commande
// Si c’est un WORD et que la commande est là : c’est un argument
// Si c’est une redirection : tu vérifies qu’il y a un WORD derrière : sinon erreur
// Si tu tombes sur un pipe : tu vérifies que t’as bien eu une commande avant : tu passes à la suite
// Si la liste se termine : tu vérifies que la dernière commande était valide

#include "minishell.h"

void create_cmds(t_token *head_token, t_token *end, t_cmds **head);

int parser(t_token *head)
{
	t_token *tmp;
	t_cmds *head_cmd;
	t_token *start;

	tmp = head;
	head_cmd = NULL;
	// si on fait entrer renvoie le prompt
	if (tmp == NULL)
		return (0); //
	// permet de retourner en arriere pour lire du debut jusqu au | ou NULL
	start = head;
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
	return (0);
}

void append_word(t_word **head, t_word *new)
{
	t_word *tmp;

	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void create_word(t_cmds *cmd, t_token *token)
{
	t_word *new;
	t_word *tmp;

	tmp = cmd->words;
	new = malloc(sizeof(t_word));
	if (!new)
	{
		cmd->leak_flag = 1;
		return (perror("Malloc failed")); // return Success mais normal, il faut faire echouer avec -1
	} //
	ft_memset(new, 0, sizeof(t_word));
	new->word = token_to_string(token);
	if (!new->word)
	{
		cmd->leak_flag = 1;
		free(new);
		return (perror("Malloc failed")); //
	}
	t_fragment *first = token->fragments;
	new->quote_type = (first ? first->quote_type : NO_QUOTE);
	append_word(&cmd->words, new);
	// ft_printf("Create word: %s quote_type %i\n", new->word, new->quote_type);
}

void append_redir(t_redir **head, t_redir *new)
{
	t_redir *tmp;

	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void create_redir(t_cmds *cmd, t_token *head)
{
	t_redir *new;
	t_redir *tmp;

	if (!head->next || !head)
		return;
	tmp = cmd->redir;
	new = malloc(sizeof(t_redir));
	if (!new)
	{
		cmd->leak_flag = 1;
		return (perror("Malloc failed")); // return Success mais normal, il faut faire echouer avec -1
	}
	ft_memset(new, 0, sizeof(t_redir));

	// on dup ce qu'il y a apres la redir
	new->filename = token_to_string(head->next);
	if (!new->filename)
	{
		free(new);
		cmd->leak_flag = 1;
		return (perror("Malloc failed")); //
	}
	t_fragment *first = head->next->fragments;
	new->quote_type = (first ? first->quote_type : NO_QUOTE);
	new->next = NULL;
	append_redir(&cmd->redir, new);
}

void lst_clear_cmds(t_word **head_w, t_redir **head_r, t_cmds **head)
{
	lst_clear((void **)head_w, get_next_word, del_word);

	lst_clear((void **)head_r, get_next_redir, del_redir);
	lst_clear((void **)head, get_next_cmds, del_cmds);
}

void add_word_and_redir(t_token *head_token, t_token *end, t_cmds *cmd)
{
	while (head_token != end->next)
	{
		// cree la liste de mot
		if (head_token->type == WORD)
		{
			create_word(cmd, head_token);
		}
		// cree la liste de redir
		else if (is_redir(head_token))
		{
			create_redir(cmd, head_token);
			head_token = head_token->next;
		}
		head_token = head_token->next;
	}
}

void create_cmds(t_token *head_token, t_token *end, t_cmds **head)
{
	t_cmds *new;
	t_cmds *tmp;

	new = malloc(sizeof(t_cmds));
	if (!new)
	{
		return (perror("Malloc failed")); // return Success mais normal, il faut faire echouer avec -1
	}
	// initialise les pointeurs de cmds a NULL
	ft_memset(new, 0, sizeof(t_cmds));
	new->leak_flag = 1;
	// parcourt la chaine de la fin du precedent pipe au suivant
	add_word_and_redir(head_token, end, new);
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
	print_elements_cmds(new->words, new->redir); // a supprimer plus tard
	lst_clear_cmds(&new->words, &new->redir, head);
}
