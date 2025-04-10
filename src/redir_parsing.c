

#include "minishell.h"

void	append_redir_parse(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/*
 * to trigger perror need to set new to -1
 * else it returns success for NULL
 * dup what is after redir
*/
void	create_redir(t_cmds *cmd, t_token *head, t_minishell *minishell)
{
	t_redir *new;

	(void)minishell;
	if (!head->next || !head)
		return ;
	new = malloc(sizeof(t_redir));
	if (!new)
	{
		cmd->leak_flag = 1;
		return (perror("Malloc failed"));
	}
	ft_memset(new, 0, sizeof(t_redir));

	if (!new->filename)
	{
		free(new);
		cmd->leak_flag = 1;
		return (perror("Malloc failed"));
	}
	new->next = NULL;
	append_redir_parse(&cmd->redir, new);
}
