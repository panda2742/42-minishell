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

char *build_word(const char *string, int *i, int *quote_type)
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
			*quote_type = DOUBLE_QUOTE;
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
			*quote_type = SINGLE_QUOTE;
			(*i)++; // skip closing quote
		}
		else
		{
			start = *i;
			while (string[*i] && !is_separator(string[*i]) && string[*i] != '\'' && string[*i] != '"')
				(*i)++;
			segment = ft_substr(string, start, *i - start);
			*quote_type = NO_QUOTE;
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
	char *word = NULL;
	t_token *head = NULL;
	int	quote_type = 0;

	while (string[i])
	{
		// Ignore les espaces
		while (ft_isspace(string[i]))
			i++;
		// Gere "" et '' et les enchainements
		if (is_word_start(string[i]))
			{
				word = build_word(string, &i, &quote_type);
				if (!word)
					return (NULL); // error
				ft_create_token(WORD, word, quote_type, &head);
				free(word);
			}
		else if (string[i] == '|')
		{
			ft_create_token(PIPE, "|", NO_QUOTE, &head);
			i++;
		}
		else if (string[i] == '>' && string[i + 1] == '>')
		{
			ft_create_token(APPEND, ">>", NO_QUOTE, &head);
			i += 2;
		}
		else if (string[i] == '<' && string[i + 1] == '<')
		{
			ft_create_token(HEREDOC, "<<", NO_QUOTE, &head);
			i += 2;
		}
		else if (string[i] == '<')
		{
			ft_create_token(REDIR_IN, "<", NO_QUOTE, &head);
			i++;
		}
		else if (string[i] == '>')
		{
			ft_create_token(REDIR_OUT, ">", NO_QUOTE, &head);
			i++;
		}
	}
	return (head);
}

