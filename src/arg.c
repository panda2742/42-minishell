
#include "minishell.h"

t_excmd	*cmd_to_arg(t_cmds *head)
{
	t_cmds *tmp_cmd;
	t_word *tmp_word;
	t_excmd *ex_new;
	t_excmd *ex_tail;
	t_excmd *ex_head;

	if (head == NULL)
		return (NULL);
	ex_head = NULL;
	ex_tail = NULL;
	tmp_cmd = head;

	while (tmp_cmd)
	{
		// Not so useful, just in case
		if (tmp_cmd->words == NULL)
		{
			tmp_cmd = tmp_cmd->next;
			continue ;
		}
		tmp_word = tmp_cmd->words;
		ex_new = malloc(sizeof(t_excmd));
		if (!ex_new)
			return (NULL); //
		ft_memset(ex_new, 0, sizeof(t_excmd));
		ex_new->argc = ft_cmd_lstsize(tmp_word);
		ex_new->argv = malloc(sizeof(char *) * (ex_new->argc + 1));
		if (!ex_new->argv)
		{
			free(ex_new);
			return (NULL);
		}
		ex_new->name = ft_strdup(tmp_word->word); // verif malloc
		int i = 0;
		while (tmp_word)
		{
			ex_new->argv[i] = ft_strdup(tmp_word->word);
			i++;
			tmp_word = tmp_word->next;
		}
		ex_new->argv[i] = NULL;
		ex_new->next = NULL;
		if (ex_head == NULL)
		{
			ex_head = ex_new;
			ex_tail = ex_new;
		}
		else
		{
			ex_tail->next = ex_new;
			ex_tail = ex_new;
		}

		tmp_cmd = tmp_cmd->next;
	}
	return (ex_head);
}