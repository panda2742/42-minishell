/*

*/

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

char *join_and_free(char *s1, const char *s2)
{
    char *result;

    result = ft_strjoin(s1, s2);
    free(s1);
    return result;
}

char *build_word(const char *string, int *i)
{
	char *word = ft_strdup(""); // chaîne a construire
	char *segment;
	int start;

	while (string[*i] && !is_separator(string[*i])) // tant qu on n est pas sur un vrai separateur
	{
		if (string[*i] == '"')
		{
			(*i)++;
			start = *i;
			while (string[*i] && string[*i] != '"')
				(*i)++;
			if (string[*i] == '\0')
				return (free(word), NULL); // quote non fermee
			segment = ft_substr(string, start, *i - start);
			(*i)++; // skip closing quote
		}
		else if (string[*i] == '\'')
		{
			(*i)++;
			start = *i;
			while (string[*i] && string[*i] != '\'')
				(*i)++;
			if (string[*i] == '\0')
				return (free(word), NULL); // quote non fermee
			segment = ft_substr(string, start, *i - start);
			(*i)++; // skip closing quote
		}
		else
		{
			start = *i;
			while (string[*i] && !is_separator(string[*i]) && string[*i] != '\'' && string[*i] != '"')
				(*i)++;
			segment = ft_substr(string, start, *i - start);
		}
		word = join_and_free(word, segment); // concatene tout
		free(segment);
	}
	return word;
}

int is_word_start(char c)
{
    return (c && !is_separator(c));
}


t_token	*ft_input(char *string)
{
	int i = 0;
	char *cpy = NULL;
	char *word = NULL;
	int start;
	t_token *head = NULL;

	while (string[i])
	{
		// Ignore les espaces
		if (ft_isspace(string[i]))
			i++;
		// Gere "" et '' et les enchainements
		if (is_word_start(string[i]))
			{
				word = build_word(string, &i);
				if (!word)
					return (NULL); // error
				ft_create_token(WORD, word, EXPAND, &head);
				free(word);
			}
			
		/*Copie le contenu des " " */
		// else if (string[i] == '"')
		// {
		// 	i++;
		// 	start = i;
		// 	while (string[i] != '"' && string[i])
		// 		i++;

		// 	// on verifie que les guillement sont bien fermees
		// 	if (string[i] == '"')
		// 	{
		// 		// on copie l ensemble des guillemets pour l envoyer a token value
		// 		cpy = ft_substr(string, start, i - start);
		// 		if (cpy == NULL)
		// 		{
		// 			ft_printf("Error: memory allocation failed\n");
		// 			return (NULL);
		// 		}
		// 		ft_create_token(WORD, cpy, EXPAND, &head);
		// 		free(cpy);
		// 		i++;
		// 	}
		// 	else
		// 		ft_printf("Error: quote not closed\n");
		// }
		// else if (string[i] == '\'')
		// {
		// 	i++;
		// 	start = i;
		// 	while (string[i] != '\'' && string[i])
		// 		i++;

		// 	// on verifie que les guillement sont bien fermees
		// 	if (string[i] == '\'')
		// 	{
		// 		// on copie l ensemble des guillemets pour l envoyer a token value
		// 		cpy = ft_substr(string, start, i - start);
		// 		if (cpy == NULL)
		// 		{
		// 			ft_printf("Error: memory allocation failed\n");
		// 			return (NULL);
		// 		}
		// 		ft_create_token(WORD, cpy, NO_EXPAND, &head);
		// 		free(cpy);
		// 		i++;
		// 	}
		// 	else
		// 		ft_printf("Error: quote not closed\n");
		// }
		else if (string[i] == '|')
		{
			ft_create_token(PIPE, "|", NO_EXPAND, &head);
			i++;
		}
		else if (string[i] == '>' && string[i + 1] == '>')
		{
			ft_create_token(APPEND, ">>", NO_EXPAND, &head);
			i += 2;
		}
		else if (string[i] == '<' && string[i + 1] == '<')
		{
			ft_create_token(HEREDOC, "<<", NO_EXPAND, &head);
			i += 2;
		}
		else if (string[i] == '<')
		{
			ft_create_token(REDIR_IN, "<", NO_EXPAND, &head);
			i++;
		}
		else if (string[i] == '>')
		{
			ft_create_token(REDIR_OUT, ">", NO_EXPAND, &head);
			i++;
		}
		else
		{
			start = i;
			while (string[i] && !is_separator(string[i]))
				i++;
			cpy = ft_substr(string, start, i - start);
			if (cpy == NULL)
			{
				ft_printf("Error: memory allocation failed\n");
				return (NULL);
			}
			ft_create_token(WORD, cpy, EXPAND, &head);
			free(cpy);
		}
	}
	return (head);
}