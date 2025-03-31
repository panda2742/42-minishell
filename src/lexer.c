/*
*/

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

t_token	*ft_input(const char *input)
{
	t_token	*token_list = NULL;
	t_token	*curr_token = NULL;
	int		index = 0;
	int		i = 0;
	int		start;

	while (input[i])
	{
		/* Sauter les espaces initiaux */
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		/* Création d'un nouveau token de type WORD */
		curr_token = ft_create_token(WORD, index++);
		/* Traitement du token jusqu'au prochain espace */
		while (input[i] && input[i] != ' ')
		{
			if (input[i] == '\'') /* Gestion des quotes simples */
			{
				i++; /* Passer la quote d'ouverture */
				start = i;
				while (input[i] && input[i] != '\'')
					i++;
				append_fragment(curr_token,
					new_fragment(input + start, i - start, SINGLE));
				if (input[i] == '\'')
					i++; /* Passer la quote de fermeture */
			}
			else if (input[i] == '\"') /* Gestion des quotes doubles */
			{
				i++; /* Passer la quote d'ouverture */
				start = i;
				while (input[i] && input[i] != '\"')
					i++;
				append_fragment(curr_token,
					new_fragment(input + start, i - start, DOUBLE));
				if (input[i] == '\"')
					i++; /* Passer la quote de fermeture */
			}
			else if (input[i] == '|')
			{
				append_fragment(curr_token, new_fragment("|", 1, NONE));
				curr_token->type = PIPE;
				i++;
			}
			else if (input[i] == '>' && input[i + 1] == '>')
			{
				append_fragment(curr_token, new_fragment(">>", 2, NONE));
				curr_token->type = APPEND;
				i += 2;
			}
			else if (input[i] == '<' && input[i + 1] == '<')
			{
				append_fragment(curr_token, new_fragment("<<", 2, NONE));
				curr_token->type = HEREDOC;
				i += 2;
			}
			else if (input[i] == '<')
			{
				append_fragment(curr_token, new_fragment("<", 1, NONE));
				curr_token->type = REDIR_IN;
				i++;
			}
			else if (input[i] == '>')
			{
				append_fragment(curr_token, new_fragment(">", 1, NONE));
				curr_token->type = REDIR_OUT;
				i++;
			}
			else /* frag sans quotes */
			{
				start = i;
				while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '\"')
					i++;
				append_fragment(curr_token,
					new_fragment(input + start, i - start, NONE));
			}
		}
		append_token(&token_list, curr_token);
	}
	return (token_list);
}


