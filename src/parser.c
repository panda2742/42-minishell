
// // Si je commence par un pipe : erreur
// // Si je trouve une redirection : il faut que je trouve un mot juste apres
// // Deux pipes qui se suivent : erreur
// // Si je termine par un pipe : erreur
// // Les quotes fermees : deja gerees dans le lexer normalement,
// // donc le parser est clean la-dessus

// // Tu pars du debut de la liste des tokens
// // Tant que ce n’est pas un pipe ou la fin :
// // Si c’est un WORD et que t’as pas de commande : c’est ta commande
// // Si c’est un WORD et que la commande est la : c’est un argument
// // Si c’est une redirection : tu verifies qu’il y a un WORD derriere : sinon erreur
// // Si tu tombes sur un pipe : tu verifies que t’as bien eu une commande avant : tu passes a la suite
// // Si la liste se termine : tu verifies que la derniere commande etait valide

// // A gerer:
// // export abc="    a     b   "
// // echo "$abc"'$abc'$abc

// #include "libft.h"
// #include "minishell.h"

// void create_cmds(t_token *head_token, t_token *end, t_cmds **head,
// 				 t_minishell *minishell);
// void process_fragment(t_fragment *frag, t_cmds *cmd, t_minishell *minishell,
// 					  char **accumulated);
// void build_token_string(t_token *token, t_minishell *minishell, t_cmds *cmd,
// 						char **result);
// void append_word(t_word **head, t_word *new);
// char *expand_var_in_string(char *str, t_minishell *minishell);
// void split_and_append_words(char *str, t_cmds *cmd);

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// /*
//  * La fonction commune d’expansion qui traite une chaîne.
//  * Elle effectue l’expansion des variables (suppression des quotes deja gerees en amont)
//  * sans field splitting.
//  * Pour chaque '$', on lit le nom maximal (caracteres alphanumeriques et '_')
//  * et on recherche la variable dans l’environnement. Si elle n’existe pas,
//  * on renvoie une chaine vide (conformement au comportement POSIX).
//  */
// char *expand_token_str_a(const char *str, t_minishell *minishell)
// {
// 	char *result;
// 	char *tmp;
// 	int i;
// 	char *var_name;
// 	t_env_var *var;
// 	const char *value;
// 	char tmp_char[2];

// 	i = 0;
// 	int start, var_len;
// 	result = ft_strdup("");
// 	if (!result)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++; // saute le '$'
// 			start = i;
// 			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 				i++;
// 			var_len = i - start;
// 			if (var_len <= 0)
// 			{
// 				tmp = ft_strjoin(result, "$");
// 				free(result);
// 				result = tmp;
// 				continue;
// 			}
// 			var_name = ft_substr(str, start, var_len);
// 			var = get_var(&minishell->env, var_name);
// 			free(var_name);
// 			value = "";
// 			if (var && var->value)
// 				value = var->value;
// 			tmp = ft_strjoin(result, value);
// 			free(result);
// 			result = tmp;
// 		}
// 		else
// 		{
// 			tmp_char[0] = str[i];
// 			tmp_char[1] = '\0';
// 			tmp = ft_strjoin(result, tmp_char);
// 			free(result);
// 			result = tmp;
// 			i++;
// 		}
// 	}
// 	return (result);
// }

// /*
//  * Accumule les fragments d’un token en appelant expand_token_str pour les fragments
//  * dont le quote_type n'est pas SINGLE (pour lesquels on se contente d'un strdup).
//  * Le resultat est une chaune allouee.
//  */
// char *accumulate_token_fragments(t_token *token, t_minishell *minishell)
// {
// 	char *accum;
// 	char *tmp;
// 	char *expanded;
// 	t_fragment *frag;

// 	accum = ft_strdup("");
// 	if (!accum)
// 		return (NULL);
// 	frag = token->fragments;
// 	while (frag)
// 	{
// 		if (frag->quote_type == SINGLE)
// 			expanded = ft_strdup(frag->text);
// 		else
// 			expanded = expand_token_str_a(frag->text, minishell);
// 		if (!expanded)
// 		{
// 			free(accum);
// 			return (NULL);
// 		}
// 		tmp = ft_strjoin(accum, expanded);
// 		free(expanded);
// 		free(accum);
// 		if (!tmp)
// 			return (NULL);
// 		accum = tmp;
// 		frag = frag->next;
// 	}
// 	return (accum);
// }

// /*
//  * token_has_unquoted : renvoie 1 s'il existe au moins un fragment dont le quote_type est NONE.
//  */
// int token_has_unquoted(t_token *token)
// {
// 	t_fragment *frag;

// 	frag = token->fragments;
// 	while (frag)
// 	{
// 		if (frag->quote_type == NONE)
// 			return (1);
// 		frag = frag->next;
// 	}
// 	return (0);
// }

// /*
//  * create_word : pour un token de type WORD,
//  * on accumule l’ensemble des fragments,
//  * puis si necessaire (cas d’un field splitting) on decoupe la chaine.
//  * Ici, si le token contient un fragment non cite ET un espace,
//  * on fait le split.
//  * Sinon, on cree un unique t_word.
//  */
// void create_word(t_cmds *cmd, t_token *token, t_minishell *minishell)
// {
// 	char *accum;
// 	char **split_words;
// 	int i;
// 	t_word *new_word;

// 	accum = accumulate_token_fragments(token, minishell);
// 	if (!accum)
// 	{
// 		cmd->leak_flag = 1;
// 		perror("Accumulation failed");
// 		return;
// 	}
// 	/* Field splitting uniquement pour les WORD tokens */
// 	if (token_has_unquoted(token) && strchr(accum, ' '))
// 	{
// 		split_words = ft_split_a(accum, ' ');
// 		free(accum);
// 		if (!split_words)
// 		{
// 			cmd->leak_flag = 1;
// 			perror("Split failed");
// 			return;
// 		}
// 		i = 0;
// 		while (split_words[i])
// 		{
// 			if (split_words[i][0] != '\0')
// 			{
// 				new_word = malloc(sizeof(t_word));
// 				if (!new_word)
// 				{
// 					cmd->leak_flag = 1;
// 					perror("Malloc failed for new word");
// 					// Ici, penser a liberer split_words et ses elements.
// 					return;
// 				}
// 				new_word->word = ft_strdup(split_words[i]);
// 				new_word->quote_type = NONE;
// 				new_word->next = NULL;
// 				append_word(&cmd->words, new_word);
// 			}
// 			i++;
// 		}
// 		// Liberation de split_words
// 		i = 0;
// 		while (split_words[i])
// 		{
// 			free(split_words[i]);
// 			i++;
// 		}
// 		free(split_words);
// 	}
// 	else
// 	{
// 		new_word = malloc(sizeof(t_word));
// 		if (!new_word)
// 		{
// 			free(accum);
// 			cmd->leak_flag = 1;
// 			perror("Malloc failed for new word");
// 			return;
// 		}
// 		new_word->word = accum;
// 		new_word->quote_type = NONE;
// 		new_word->next = NULL;
// 		/* Si le token etait compose de fragments non cites et l'accumulation est vide,
// 			on ne cree pas le mot (deja traite par le split). */
// 		if (token_has_unquoted(token) && new_word->word[0] == '\0')
// 		{
// 			free(new_word->word);
// 			free(new_word);
// 			return;
// 		}
// 		append_word(&cmd->words, new_word);
// 	}
// }

// /*
//  * create_redir_arg : pour un token servant d’argument de redirection (type REDIR_ARG),
//  * on accumule l’ensemble des fragments ET on applique l’expansion sans field splitting.
//  */
// void create_redir_arg(t_cmds *cmd, t_token *token, t_minishell *minishell)
// {
// 	char *accum;
// 	t_word *new_word;

// 	accum = accumulate_token_fragments(token, minishell);
// 	if (!accum)
// 	{
// 		cmd->leak_flag = 1;
// 		perror("Accumulation failed");
// 		return;
// 	}
// 	// Ici, on ne fait PAS de field splitting meme si des espaces sont presents.
// 	new_word = malloc(sizeof(t_word));
// 	if (!new_word)
// 	{
// 		free(accum);
// 		cmd->leak_flag = 1;
// 		perror("Malloc failed for redir arg");
// 		return;
// 	}
// 	new_word->word = accum;
// 	new_word->quote_type = REDIR_ARG; // On marque differemment
// 	new_word->next = NULL;
// 	append_word(&cmd->words, new_word);
// }

// /*
//  * append_word : Ajoute un t_word a la fin de la liste.
//  */
// void append_word(t_word **head, t_word *new)
// {
// 	t_word *tmp;

// 	if (!*head)
// 	{
// 		*head = new;
// 		return;
// 	}
// 	tmp = *head;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

// /*
//  * Dans add_word_and_redir, on parcourt la liste des tokens.
//  * Lorsqu'un token de redirection est rencontre (is_redir),
//  * on verifie que le token suivant existe et on change son type en REDIR_ARG,
//  * puis on appelle create_redir_arg.
//  * Pour les tokens de type WORD, on appelle create_word.
//  */
// void add_word_and_redir(t_token *head_token, t_token *end, t_cmds *cmd,
// 						t_minishell *minishell)
// {
// 	while (head_token != end->next)
// 	{
// 		if (head_token->type == WORD)
// 		{
// 			create_word(cmd, head_token, minishell);
// 		}
// 		else if (is_redir(head_token))
// 		{
// 			head_token = head_token->next;
// 			if (!head_token)
// 			{
// 				// Erreur de syntaxe : redirection sans argument.
// 				return;
// 			}
// 			head_token->type = REDIR_ARG;
// 			create_redir_arg(cmd, head_token, minishell);
// 		}
// 		head_token = head_token->next;
// 	}
// }

// int parser(t_token *head, t_minishell *minishell)
// {
// 	t_token *tmp;
// 	t_cmds *head_cmd;
// 	t_token *start;

// 	tmp = head;
// 	head_cmd = NULL;
// 	if (tmp == NULL)
// 		return (0);
// 	start = head;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->type == PIPE || tmp->next == NULL)
// 		{
// 			create_cmds(start, tmp, &head_cmd, minishell);
// 			start = tmp->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// void lst_clear_cmds(t_word **head_w, t_redir **head_r, t_cmds **head)
// {
// 	lst_clear((void **)head_w, get_next_word, del_word);
// 	lst_clear((void **)head_r, get_next_redir, del_redir);
// 	lst_clear((void **)head, get_next_cmds, del_cmds);
// }

// void process_cmds(t_cmds *head)
// {
// 	t_cmds *tmp_cmd;
// 	t_word *tmp_word;

// 	if (!head)
// 		return;
// 	tmp_cmd = head;
// 	while (tmp_cmd)
// 	{
// 		tmp_word = tmp_cmd->words;
// 		while (tmp_word)
// 		{
// 			ft_printf("Word exec: %s\n", tmp_word->word);
// 			tmp_word = tmp_word->next;
// 		}
// 		tmp_cmd = tmp_cmd->next;
// 	}
// }
// // void create_cmds(t_token *head_token, t_token *end, t_cmds **head,
// // 				 t_minishell *minishell)
// // {
// // 	t_cmds *new;
// // 	t_cmds *tmp;
// // 	t_word *tmp_word;
// // 	t_excmd *ex_cmd;

// // 	new = malloc(sizeof(t_cmds));
// // 	if (!new)
// // 	{
// // 		perror("Malloc failed");
// // 		return;
// // 	}
// // 	ft_memset(new, 0, sizeof(t_cmds));
// // 	new->leak_flag = 1;
// // 	add_word_and_redir(head_token, end, new, minishell);
// // 	if (!*head)
// // 		*head = new;
// // 	else
// // 	{
// // 		tmp = *head;
// // 		while (tmp->next)
// // 			tmp = tmp->next;
// // 		tmp->next = new;
// // 	}
// // 	// Conversion de t_cmds en t_excmd
// // 	tmp_word = new->words;
// // 	while (tmp_word)
// // 	{
// // 		ft_printf("Word cmd : %s\n", tmp_word->word);
// // 		tmp_word = tmp_word->next;
// // 	}
// // 	ex_cmd = cmd_to_arg((*head));
// // 	(void)ex_cmd;
// // 	// ft_printf("excmd %s\n", ex_cmd->name);
// // 	process_cmds(*head);
// // 	lst_clear_cmds(&new->words, &new->redir, head);
// // }
