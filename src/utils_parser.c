
#include "minishell.h"

const char	*get_token_type_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

int	is_redir(t_token *head_token)
{
	return (head_token->type == REDIR_IN || head_token->type == REDIR_OUT
		|| head_token->type == APPEND || head_token->type == HEREDOC);
}