
#include "libft.h"
#include "minishell.h"
#include <unistd.h>

static void handle_redir_in(const char *input, int *i, t_token **token_list)
{
	t_token *token;

	if (input[(*i) + 1] && input[(*i) + 1] == '<')
	{
		token = ft_create_token(HEREDOC);
		if (!token)
			return; /// gestion d erreur
		append_fragment(token, new_fragment("<<", 2, SINGLE));
		;
		(*i) += 2;
	}
	else
	{
		token = ft_create_token(REDIR_IN);
		if (!token)
			return; /// gestion d erreur
		append_fragment(token, new_fragment("<", 1, SINGLE));
		(*i)++;
	}
	append_token(token_list, token);
}

void handle_redir_out(const char *input, int *i, t_token **token_list)
{
	t_token *token;

	if (input[(*i) + 1] && input[(*i) + 1] == '>')
	{
		token = ft_create_token(APPEND);
		if (!token)
			return; /// gestion d erreur
		append_fragment(token, new_fragment(">>", 2, SINGLE));

		(*i) += 2;
	}
	else
	{
		token = ft_create_token(REDIR_OUT);
		if (!token)
			return; /// gestion d erreur
		append_fragment(token, new_fragment(">", 1, SINGLE));
		(*i)++;
	}
	append_token(token_list, token);
}

void handle_pipe(int *i, t_token **token_list)
{
	t_token *token;

	token = ft_create_token(PIPE);
	if (!token)
		return; // gestion d erreur
	append_fragment(token, new_fragment("|", 1, SINGLE));
	append_token(token_list, token);
	(*i)++;
}

/*
 * Handle | and every kind of redir
 */
void handle_redir_pipe(int *i, t_token **token_list, const char *input)
{
	if (input[*i] == '|')
	{
		handle_pipe(i, token_list);
	}
	else if (input[*i] == '<')
	{
		handle_redir_in(input, i, token_list);
	}
	else if (input[*i] == '>')
	{
		handle_redir_out(input, i, token_list);
	}
}

static int parse_single_quote(t_token *token, const char *input, int *i)
{
	int start;

	(*i)++; // skip quote
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] != '\'')
	{
		ft_printf("Quotes not closed\n");
		return (0);
	}
	append_fragment(token, new_fragment(input + start, *i - start, SINGLE));
	(*i)++; // skip quote
	return (1);
}

static int parse_double_quote(t_token *token, const char *input, int *i)
{
	int start;

	(*i)++; // skip quote
	start = *i;
	while (input[*i] && input[*i] != '\"')
		(*i)++;
	if (input[*i] != '\"')
	{
		ft_printf("Quotes not closed\n");
		return (0);
	}
	append_fragment(token, new_fragment(input + start, *i - start, DOUBLE));
	(*i)++; // skip quote
	return (1);
}

static int parse_unquoted(t_token *token, const char *input, int *i)
{
	int start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_char_redir_or_pipe(input[*i]) &&
		   input[*i] != '\'' && input[*i] != '\"')
	{
		(*i)++;
	}
	append_fragment(token, new_fragment(input + start, *i - start, NONE));
	return (1);
}

/*
** Construit un token WORD en accumulant ses fragments jusqu'a rencontrer un delimiteur.
*/
static t_token *parse_word_token(const char *input, int *i)
{
	t_token *token;

	token = ft_create_token(WORD);
	if (token == NULL)
		return (NULL);
	while (input[*i] && !ft_isspace(input[*i]) && !is_char_redir_or_pipe(input[*i]))
	{
		if (input[*i] == '\'')
		{
			if (parse_single_quote(token, input, i) == 0)
				return (NULL);
		}
		else if (input[*i] == '\"')
		{
			if (parse_double_quote(token, input, i) == 0)
				return (NULL);
		}
		else
		{
			if (parse_unquoted(token, input, i) == 0)
				return (NULL);
		}
	}
	return (token);
}

/*
** Pour chaque element de la chaine d'entree, on saute les espaces,
** on gere les tokens de redirection/pipe via handle_redir_pipe, ou on construit
** un token WORD en accumulant ses fragments.
*/
t_token *ft_input(const char *input)
{
	t_token *token_list;
	t_token *curr_token;
	int i;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break;
		if (is_char_redir_or_pipe(input[i]))
		{
			handle_redir_pipe(&i, &token_list, input);
			continue;
		}
		curr_token = parse_word_token(input, &i);
		if (curr_token == NULL)
			return (NULL);
		append_token(&token_list, curr_token);
	}
	return (token_list);
}
