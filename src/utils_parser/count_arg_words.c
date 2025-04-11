
#include "minishell.h"

size_t	count_arg_words(t_token *token)
{
	t_token *tmp = token;
	size_t	nb_of_words;
	
	nb_of_words = 0;
	if (!token)
		return (0);
	while (tmp)
	{
		if (tmp->type == WORD)
			nb_of_words++;
		tmp = tmp->next;
	}
	return (nb_of_words);
}
