

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

void	update_token_redir(t_token *list)
{
	t_fragment *tmp;
	
	tmp = list->next->fragments;
	list->next->type = REDIR_ARG;
	while (tmp)
	{
		tmp->quote_type = DOUBLE;
		tmp = tmp->next;
	}
}

int	ft_printf_error(char *str)
{
	ft_printf("%s", str);
	return (0);
}

static int	check_redir_error(t_token *token)
{
	if (token->next == NULL)
		return (ft_printf_error("syntax error near unexpected token `newline'\n"));
	if (token->next->type != WORD)
		return (ft_printf_error("syntax error near unexpected token `newline'\n"));
	update_token_redir(token);
	return (1);
}

static int	check_pipe_error(t_token *token)
{
	if (token->next == NULL)
		return (ft_printf_error("Syntax error end with a | not allowed\n"));
	if (token->next->type == PIPE)
		return (ft_printf_error("Syntax error || detected\n"));
	return (1);
}

int	lexer_parse(t_token *token)
{
	t_token *list = token;
	// t_token *tmp = token;
	if (list == NULL)
		return (0);
	if (list->type == PIPE)
		return ft_printf_error("Error: syntax error near unexpected token `|'\n"); //
	while (list != NULL)
	{
		if (list->type == PIPE)
		{
			if (check_pipe_error(list) == 0)
				return (0);
		}
		if (is_redir(list) != 0)
		{
			if (check_redir_error(list) == 0)
				return (0);
		}
		list = list->next;
	}
	return (1);
}
