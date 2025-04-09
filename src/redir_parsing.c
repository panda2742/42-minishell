

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
void	create_redir(t_cmds *cmd, t_token *head, t_minishell *minishell)
{
	t_redir *new;
	// t_redir *tmp;
	(void)minishell;
	if (!head->next || !head)
		return ;
	// tmp = cmd->redir;
	new = malloc(sizeof(t_redir));
	if (!new)
	{
		cmd->leak_flag = 1;
		return (perror("Malloc failed")); // return Success mais normal,
//			il faut faire echouer avec -1
	}
	ft_memset(new, 0, sizeof(t_redir));
	// on dup ce qu'il y a apres la redir
	// new->filename = token_to_string(head->next, minishell);
	if (!new->filename)
	{
		free(new);
		cmd->leak_flag = 1;
		return (perror("Malloc failed")); //
	}
	// t_fragment *first = head->next->fragments;
	new->next = NULL;
	append_redir_parse(&cmd->redir, new);
}