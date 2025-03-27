
#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int return_empty(t_token *token)
{
	return(!ft_strcmp(token->value, ":") || !ft_strcmp(token->value, "!"));
}


int lexer_parse(t_token *token)
{
	// que des espaces
	if (token == NULL)
	{
		return (0);
	}
	if (return_empty(token))
	{
		return (0);
	}
	// ne peut peut pas commencer par un pipe
	if (token->type == PIPE)
	{
			ft_printf("Error: syntax error near unexpected token `|'\n"); //
			return 0; //
	}
	while (token != NULL)
	{
		if (token->next != NULL)
		{
			// pas de double ||
			if (token->type == PIPE && token->next->type == PIPE)
			{
				ft_printf("Syntax error || detected\n");
				return 0; //
			}
		}
		// ne peut pas terminer par un |
		if (token->type == PIPE && token->next == NULL)
		{
			ft_printf("Syntax error end with a | not allowed\n");
			return 0;
		}
		// verifie ce qu'il y a apres une redir
		if (is_redir(token))
		{

			if (token->next == NULL)
			{
				ft_printf("bash: syntax error near unexpected token `newline'\n");
				return (0);
			}
			if (token->next->type != WORD)
			{
				ft_printf("bash: syntax error near unexpected redir\n");
				return (0);
			}
		}
		ft_printf("Type is: %d, value is %s, index is %i, expand %i\n", token->type, token->value, token->index, token->expand);
		token = token->next;
	}
	return 1;
}