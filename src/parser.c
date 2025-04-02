

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

void create_cmds(t_token *head_token, t_token *end, t_cmds **head, t_minishell *minishell);

int parser(t_token *head, t_minishell *minishell)
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
			create_cmds(start, tmp, &head_cmd, minishell);
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

void create_word(t_cmds *cmd, t_token *token, t_minishell *minishell)
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
	new->word = token_to_string(token, minishell, cmd);
	if (!new->word)
	{
		cmd->leak_flag = 1;
		free(new);
		return (perror("Malloc failed")); //
	}
	// t_fragment *first = token->fragments;
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

char *expand_var_in_string(char *str, t_minishell *minishell)
{
	char *expanded;
	char *tmp;
	t_env_var *var = NULL;
	int i;
	int start;

	expanded = ft_strdup("");
	if (!expanded)
		return NULL;
	i = 0;
	if (ft_strchr(str, '$') == 0)
		return (expanded = ft_strdup(str));
	else
	{
		while (str[i])
		{
			if (str[i] == '$')
			{
				i++; // skip le $
				start = i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				if (start == i) // means there is nothing else than a $
				{
					tmp = ft_strjoin(expanded, "$");
					free(expanded);
					expanded = tmp;
					continue;
				}
				char *tmp_var = ft_substr(str, start, i - start);
				var = get_var(&minishell->env, tmp_var);
				free(tmp_var); // the part after $
				const char *value = "";
				if (var && var->value)
					value = var->value;
				char *tmp = ft_strjoin(expanded, value);
				free(expanded);
				expanded = tmp;
			}
			else
			{
				char tmp_char[2];
				tmp_char[0] = str[i];
				tmp_char[1] = '\0';
				char *tmp = ft_strjoin(expanded, tmp_char);
				free(expanded);
				expanded = tmp;
				i++;
			}
		}
	}
	return (expanded);
}

void split_unquote_words(char *str, t_word **head)
{
	char **tab;
	int i;
	t_word *new_word;

	i = 0;
	tab = ft_split(str, " ");
	new_word = malloc(sizeof(t_word));
	if (!new_word)
	{
		free(tab); // // //
		return ;
	}
	while (tab[i])
	{
		new_word->word = tab[i];
		new_word->quote_type = NONE;
		new_word->next = NULL;
		i++;
	}
	append_word(head, new_word);
}

char *token_to_string(t_token *token, t_minishell *minishell, t_cmds *cmd)
{
	t_fragment *frag;
	char *result;
	char *tmp;
	char *expanded;

	frag = token->fragments;
	result = ft_strdup("");
	if (!result)
		return NULL;
	while (frag)
	{
		if (frag->quote_type == SINGLE)
			expanded = ft_strdup((const char *)frag->next);
		else
		{
			expanded = expand_var_in_string(token->fragments->text, minishell);
			if (frag->quote_type == NONE && ft_strchr(expanded, ' '))
			{
				split_unquote_words(expanded, &cmd->words);
			}
		}
		tmp = ft_strjoin(result, expanded);
		free(result);
		free(expanded);
		result = tmp;
		frag = frag->next;
	}
	ft_printf("Token to string result: %s \n", result);
	return (result);
}

void create_redir(t_cmds *cmd, t_token *head, t_minishell *minishell)
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
	new->filename = token_to_string(head->next, minishell, cmd);
	if (!new->filename)
	{
		free(new);
		cmd->leak_flag = 1;
		return (perror("Malloc failed")); //
	}
	// t_fragment *first = head->next->fragments;
	new->next = NULL;
	append_redir(&cmd->redir, new);
}

void lst_clear_cmds(t_word **head_w, t_redir **head_r, t_cmds **head)
{
	lst_clear((void **)head_w, get_next_word, del_word);

	lst_clear((void **)head_r, get_next_redir, del_redir);
	lst_clear((void **)head, get_next_cmds, del_cmds);
}

void add_word_and_redir(t_token *head_token, t_token *end, t_cmds *cmd, t_minishell *minishell)
{
	while (head_token != end->next)
	{
		// cree la liste de mot
		if (head_token->type == WORD)
		{
			create_word(cmd, head_token, minishell);
		}
		// cree la liste de redir
		else if (is_redir(head_token))
		{
			create_redir(cmd, head_token, minishell);
			head_token = head_token->next;
		}
		head_token = head_token->next;
	}
}

void create_cmds(t_token *head_token, t_token *end, t_cmds **head, t_minishell *minishell)
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
	add_word_and_redir(head_token, end, new, minishell);
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
	// print_elements_cmds(new->words, new->redir); // a supprimer plus tard
	// lst_clear_cmds(&new->words, &new->redir, head);
}
