

#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	lexer_parse(t_token *list)
{
	if (list == NULL)
	{
		return (0);
	}
	// else if (!ft_strcmp(list->fragments->text, ":") || !ft_strcmp(list->fragments->text, "!"))
	// {
	// 	return (0);
	// }
	if (list->type == PIPE)
	{
		ft_printf("Error: syntax error near unexpected token `|'\n"); //
		return (0);	
	}
	while (list != NULL)
	{
		if (list->next != NULL)
		{
			if (list->type == PIPE && (list->next->type == PIPE))
			{
				ft_printf("Syntax error || detected\n");
				return (0); //
			}
		}
		// check si |	|
		// else if (list->next != NULL)
		// {
		// 	if (list->fragments->text[0] == '|' && list->next->fragments->text[0] == '|')
		// 	{
		// 		ft_printf("Syntax error || detected\n");
		// 		return (0); //
		// 	}
		// }
		// ne peut pas terminer par un |
		else if (list->type == PIPE && list->next == NULL)
		{
			ft_printf("Syntax error end with a | not allowed\n");
			return (0);
		}
		list = list->next;
	}
	return (1);
}