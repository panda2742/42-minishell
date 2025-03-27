
#include "minishell.h"

int lexer_parse(t_token *token)
{
	if (token->type == PIPE)
	{
			ft_printf("Error: syntax error near unexpected token `|'\n"); //
			return 0; //
	}
	while (token != NULL)
	{
		if (token->next != NULL)
		{

			if (token->type == PIPE && token->next->type == PIPE && token->next != NULL)
			{
				ft_printf("Syntax error || detected\n");
				return 0; //
			}
		}
		ft_printf("Type is: %d, value is %s, index is %i, expand %i\n", token->type, token->value, token->index, token->expand);
		token = token->next;
	}
	return 1;
}