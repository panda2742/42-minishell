/*
 
*/

#include <unistd.h>
#include "libft.h"
#include "minishell.h"


t_token	*ft_input(char *string)
{
	int i = 0;
	char *cpy = NULL;
	int start;
	t_token *head = NULL;

	while (string[i])
	{
		// Ignore les espaces
		if (ft_isspace(string[i]))
			i++;

		/*Copie le contenu des " " */
		else if(string[i] == '"')
		{
			i++;
			start = i;
			while (string[i] != '"' && string[i])
				i++;
			
			// on verifie que les guillement sont bien fermees
			if (string[i] == '"')
			{
				// on copie l ensemble des guillemets pour l envoyer a token value
				cpy = ft_substr(string, start, i - start);
				if (cpy == NULL)
				{
					ft_printf("Error: memory allocation failed\n");
					return (NULL);
				}
				ft_create_token(WORD, cpy, EXPAND, &head);
				free(cpy);
				i++;
			}
			else
				ft_printf("Error: quote not closed\n");
		}
		else if(string[i] == '\'')
		{
			i++;
			start = i;
			while (string[i] != '\'' && string[i])
				i++;
			
			// on verifie que les guillement sont bien fermees
			if (string[i] == '\'')
			{
				// on copie l ensemble des guillemets pour l envoyer a token value
				cpy = ft_substr(string, start, i - start);
				if (cpy == NULL)
				{
					ft_printf("Error: memory allocation failed\n");
					return (NULL);
				}
				ft_create_token(WORD, cpy, NO_EXPAND, &head);
				free(cpy);
				i++;
			}
			else
				ft_printf("Error: quote not closed\n");
		}
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