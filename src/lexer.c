
#include "libft.h"
#include "minishell.h"
#include <unistd.h>



static void skip_spaces(const char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t' || input[*i] == '\n'))
		(*i)++;
}
static void	handle_redir_in(const char *input, int *i, t_token **token_list)
{
	t_token *token;

	if (input[(*i) + 1] && input[(*i) + 1] == '<')
	{
		token = ft_create_token(HEREDOC);
		if (!token)
			return ; /// gestion d erreur
		append_fragment(token, new_fragment("<<", 2, SINGLE));;
		(*i) += 2;
	}
	else
	{
		token = ft_create_token(REDIR_IN);
		if (!token)
			return ; /// gestion d erreur
		append_fragment(token, new_fragment("<", 1, SINGLE));
		(*i)++;
	}
	append_token(token_list, token);
}

void	handle_redir_out(const char *input, int *i, t_token **token_list)
{
	t_token *token;

	if (input[(*i) + 1] && input[(*i) + 1] == '>')
	{
		token = ft_create_token(HEREDOC);
		if (!token)
			return ; /// gestion d erreur
		append_fragment(token, new_fragment(">>", 2, SINGLE));
		
		(*i) += 2;
	}
	else
	{
		token = ft_create_token(REDIR_IN);
		if (!token)
			return ; /// gestion d erreur
		append_fragment(token, new_fragment(">", 1, SINGLE));
		(*i)++;
	}
	append_token(token_list, token);
}

void	handle_pipe(int *i, t_token **token_list)
{
	t_token *token;

	token = ft_create_token(PIPE);
	if (!token)
		return ; // gestion d erreur
	append_fragment(token, new_fragment("|", 1, SINGLE));
	append_token(token_list, token);
	(*i)++;
}

t_token	*ft_input(const char *input)
{
	t_token	*token_list;
	t_token	*curr_token;
	int		i;
	int		start;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		// Gestion du PIPE
		if (input[i] == '|')
		{
			handle_pipe(&i, &token_list);
			continue ;
		}
		// Gestion des redirections d'entrée et de sortie
		if (input[i] == '<')
		{
			handle_redir_in(input, &i, &token_list);
			continue ;
		}
		if (input[i] == '>')
		{
			handle_redir_out(input, &i, &token_list);
			continue ;
		}
		// Création d'un token WORD
		curr_token = ft_create_token(WORD);
		if (!curr_token)
			return (NULL);
		/*
		** On accumule dans le token WORD tous les caractères jusqu'à rencontrer un délimiteur.
		** Les délimiteurs sont : espace, tabulation, saut de ligne, pipe et redirections.
		*/
		while (input[i] && input[i] != ' ' && input[i] != '\t' && input[i] != '\n' &&
			input[i] != '|' && input[i] != '<' && input[i] != '>')
		{
			if (input[i] == '\'') // Traitement des quotes simples
			{
				i++; // On saute l'apostrophe ouvrante
				start = i;
				while (input[i] && input[i] != '\'')
					i++;
				if (input[i] == '\'')
				{
					append_fragment(curr_token,
						new_fragment((char *)(input + start), i - start, SINGLE));
					i++; // On saute l'apostrophe fermante
				}
				else
				{
					ft_printf("Quotes not closed\n"); /* Quotes not closed */
					// Ici, il faudrait libérer curr_token et ses fragments
					return (NULL);
				}
			}
			else if (input[i] == '\"') // Traitement des quotes doubles
			{
				i++; // On saute la quote ouvrante
				start = i;
				while (input[i] && input[i] != '\"')
					i++;
				if (input[i] == '\"')
				{
					append_fragment(curr_token,
						new_fragment((char *)(input + start), i - start, DOUBLE));
					i++; // On saute la quote fermante
				}
				else
				{
					ft_printf("Quotes not closed\n"); /* Quotes not closed */
					return (NULL);
				}
			}
			else // Traitement d'une partie non citée
			{
				start = i;
				while (input[i] && input[i] != ' ' && input[i] != '\t' &&
					input[i] != '\n' && input[i] != '|' && input[i] != '<' && input[i] != '>' &&
					input[i] != '\'' && input[i] != '\"')
					i++;
				append_fragment(curr_token,
					new_fragment((char *)(input + start), i - start, NONE));
			}
		}
		append_token(&token_list, curr_token);
	}
	return (token_list);
}
