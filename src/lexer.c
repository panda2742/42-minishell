/*
 Les espaces n'ont aucun impact
*/



#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void ft_lexer(void)
{
	write(1, "1", 1);
}


t_token	*ft_input(char *string)
{
	int i = 0;
	char *cpy = NULL;
	t_token *head = NULL;

	while (string[i])
	{
		if (ft_isspace(string[i]))
			i++;
		/*Copie le contenu des " " */
		else if(string[i] == '"')
		{
			i++;
			int pos = i;
			while (string[i] != '"')
				i++;
			cpy = malloc((i - pos) + 1);
			if (!cpy)
			{
				free(string);
				return NULL;
			}
			int y = 0;
			while (string[pos] != '"')
			{
				cpy[y] = string[pos];
				y++;
				pos++;
			}
			cpy[y] = '\0';
			// Probleme avec le gnl qui renvoie un peu de la merde
			if (string[i] == '"')
				i++;
			t_token *token = malloc(sizeof(t_token));
			token->type = WORD;
			token->value = ft_strdup(cpy);
			free(cpy);
			token->next = NULL;
			head = token;
		}
		else
			i++;
	}
	ft_printf("Input is: %s\n", string);
	return (head);
}