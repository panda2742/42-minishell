
#include "libft.h"
#include "minishell.h"

// renvoie  positif si c == quelque chose
int	is_token(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_separator(char c)
{
	return (ft_isspace(c) || is_token(c));
}


void	print_tokens(t_token *tokens)
{
	t_token		*tmp_token;
	t_fragment	*tmp_frag;

	tmp_token = tokens;
	while (tmp_token)
	{
		printf("Token %d (type %d): ", tmp_token->index, tmp_token->type);
		tmp_frag = tmp_token->fragments;
		while (tmp_frag)
		{
			printf("[%s, quote %d] ", tmp_frag->text, tmp_frag->quote_type);
			tmp_frag = tmp_frag->next;
		}
		printf("\n");
		tmp_token = tmp_token->next;
	}
}