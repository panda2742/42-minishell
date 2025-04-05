
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
		/* skip spaces */
		while (input[i] && (input[i] == ' ' || input[i] == '\t' || input[i] == '\n'))
			i++;
		if (!input[i])
			break ;
		
		// handle types, if types new loop starts
		if (input[i] == '|')
		{
			curr_token = ft_create_token(PIPE, index++);
			append_token(&token_list, curr_token);
			i++;
			continue ;
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] && input[i + 1] == '<')
			{
				curr_token = ft_create_token(HEREDOC, index++);
				append_token(&token_list, curr_token);
				i += 2;
				continue ;
			}
			else
			{
				curr_token = ft_create_token(REDIR_IN, index++);
				append_token(&token_list, curr_token);
				i++;
				continue ;
			}
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] && input[i + 1] == '>')
			{
				curr_token = ft_create_token(APPEND, index++);
				append_token(&token_list, curr_token);
				i += 2;
				continue ;
			}
			else
			{
				curr_token = ft_create_token(REDIR_OUT, index++);
				append_token(&token_list, curr_token);
				i++;
				continue ;
			}
		}

		/* new token word */
		curr_token = ft_create_token(WORD, index++);
		if (!curr_token)
			return (NULL);

		/* working on the toke till next space */
		while (input[i] && input[i] != ' ' && input[i] != '\t' && input[i] != '|' && input[i] != '<' && input[i] != '>')
		{
			if (input[i] == '\'') /* simple quotes */
			{
				i++; /* skip quotes */
				start = i;
				while (input[i] && input[i] != '\'')
					i++;
				append_fragment(curr_token,
					new_fragment(input + start, i - start, SINGLE));
				if (input[i] == '\'')
					i++; /* skip last quote */
				else
				{
					free(curr_token->fragments->text);
					free(curr_token->fragments);
					free(curr_token);
					ft_printf("Quotes not closed\n");
					return NULL;
				}
			}
			else if (input[i] == '\"') /* double quotes*/
			{
				i++; /* skip quotes */
				start = i;
				while (input[i] && input[i] != '\"')
					i++;
				append_fragment(curr_token,
					new_fragment(input + start, i - start, DOUBLE));
				if (input[i] == '\"')
					i++; /* skip last quote */
				else
				{
					free(curr_token->fragments->text);
					free(curr_token->fragments);
					free(curr_token);
					ft_printf("Quotes not closed\n");
					return NULL;
				}
			}
			else /* frag sans quotes */
			{
				start = i;
				while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '<' && input[i] != '>' &&
					input[i] != '\'' && input[i] != '\"')
					i++;
				append_fragment(curr_token,
					new_fragment(input + start, i - start, NONE));
			}
		}
		append_token(&token_list, curr_token);
	}
	return (token_list);
}
