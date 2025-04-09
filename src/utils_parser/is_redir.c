
#include "minishell.h"

int	is_redir(t_token *head_token)
{
	return (head_token->type == REDIR_IN || head_token->type == REDIR_OUT
		|| head_token->type == APPEND || head_token->type == HEREDOC);
}