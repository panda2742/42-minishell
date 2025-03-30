/*
*/

#include "libft.h"
#include "minishell.h"
#include <unistd.h>


t_fragment *create_fragment(char *text, int quote_type)
{
	t_fragment *new = malloc(sizeof(t_fragment));
	if (!new)
		return (NULL);
	new->text = text;
	new->quote_type = quote_type;
	new->next = NULL;
	return (new);
}

void append_fragment(t_fragment **head, t_fragment *new)
{
	t_fragment *tmp;

	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_fragment *build_word(const char *str, int *i)
{
	t_fragment *frags = NULL;
	char *segment;
	int start;
	int qt;

	while (str[*i] && !is_separator(str[*i]))
	{
		qt = NO_QUOTE;
		if (str[*i] == '"')
		{
			qt = DOUBLE_QUOTE;
			(*i)++;
			start = *i;
			while (str[*i] && str[*i] != '"')
				(*i)++;
			segment = ft_substr(str, start, *i - start);
			if (str[*i]) (*i)++;
		}
		else if (str[*i] == '\'')
		{
			qt = SINGLE_QUOTE;
			(*i)++;
			start = *i;
			while (str[*i] && str[*i] != '\'')
				(*i)++;
			segment = ft_substr(str, start, *i - start);
			if (str[*i]) (*i)++;
		}
		else
		{
			start = *i;
			while (str[*i] && !is_separator(str[*i]) && str[*i] != '"' && str[*i] != '\'')
				(*i)++;
			segment = ft_substr(str, start, *i - start);
		}
		append_fragment(&frags, create_fragment(segment, qt));
	}
	return frags;
}




int is_word_start(char c)
{
    return (c && !is_separator(c));
}

char *token_to_string(t_token *token)
{
	t_fragment *frag = token->fragments;
	char *result = ft_strdup("");
	char *tmp;

	while (frag)
	{
		tmp = result;
		result = ft_strjoin(result, frag->text);
		free(tmp);
		frag = frag->next;
	}
	return result;
}

t_token	*ft_input(char *string)
{
	int i = 0;
	t_token *head = NULL;

	while (string[i])
	{
		// Ignore les espaces
		while (ft_isspace(string[i]))
			i++;
		// Gere "" et '' et les enchainements
		if (is_word_start(string[i]))
		{
			t_fragment *frags = build_word(string, &i);
			if (!frags)
				return (NULL);
			ft_create_token(WORD, frags, &head);
		}
		else if (string[i] == '|')
		{
			t_fragment *frag = create_fragment(ft_strdup("|"), NO_QUOTE);

			ft_create_token(PIPE, frag, &head);
			i++;
		}
		else if (string[i] == '>' && string[i + 1] == '>')
		{
			t_fragment *frag = create_fragment(ft_strdup(">>"), NO_QUOTE);
			ft_create_token(APPEND, frag, &head);
			i += 2;
		}
		else if (string[i] == '<' && string[i + 1] == '<')
		{
			t_fragment *frag = create_fragment(ft_strdup("<<"), NO_QUOTE);

			ft_create_token(HEREDOC, frag, &head);
			i += 2;
		}
		else if (string[i] == '<')
		{
			t_fragment *frag = create_fragment(ft_strdup("<"), NO_QUOTE);

			ft_create_token(REDIR_IN, frag, &head);
			i++;
		}
		else if (string[i] == '>')
		{
			t_fragment *frag = create_fragment(ft_strdup(">"), NO_QUOTE);
			ft_create_token(REDIR_OUT, frag, &head);
			i++;
		}
	}
	return (head);
}

