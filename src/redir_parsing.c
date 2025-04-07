

#include "minishell.h"

char *token_to_string(t_token *token, t_minishell *minishell)
{
	t_fragment *frag = token->fragments;
	t_env_var *var = NULL;
	char *result = ft_strdup("");
	int x = 0;
	int *ptr_x = &x;
	if (!result)
		return NULL; //
	char *tmp;
	while (frag)
	{
		tmp = result;
		if (frag->quote_type == SINGLE)
			result = ft_strjoin(result, frag->text);
		else
		{
			char *final_txt = NULL;
			int i = 0;
			const char *tmp_txt = frag->text;
			if (ft_strchr(tmp_txt, '$') != 0)
			{
				while (frag->text[i] != '\0')
				{
					if (frag->text[i] == '$')
					{
						i++;
						int pos = i;
						while (frag->text[i] && frag->text[i] != ' ' && frag->text[i] != '$')
							i++;
						// final_txt = ft_substr(frag->text, 0, i);
						// ft_printf("subst value %s\n", ft_substr(frag->text, pos, i));
						var = get_var(&minishell->env, ft_substr(frag->text, pos, i));
						ft_printf("var value %s\n", var->value);
						final_txt = ft_strjoin(final_txt, var->value);
						ft_printf("final text = %s\n", final_txt);
						*ptr_x = i;
						// final_txt = ft_strjoin(final_txt, )
					}
					else
						i++;
				}
			}
			else
			{

				final_txt = ft_strdup(frag->text);
				ft_printf("final text = %s\n", final_txt);
				result = ft_strjoin(result, final_txt);
				free(final_txt);
			}
		}
		free(tmp);
		frag = frag->next;
	}
	return result;
}

void append_redir_parse(t_redir **head, t_redir *new)
{
	t_redir *tmp;

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
void create_redir(t_cmds *cmd, t_token *head, t_minishell *minishell)
{
	t_redir *new;
	// t_redir *tmp;

	if (!head->next || !head)
		return;
	// tmp = cmd->redir;
	new = malloc(sizeof(t_redir));
	if (!new)
	{
		cmd->leak_flag = 1;
		return (perror("Malloc failed")); // return Success mais normal, il faut faire echouer avec -1
	}
	ft_memset(new, 0, sizeof(t_redir));
	// on dup ce qu'il y a apres la redir
	new->filename = token_to_string(head->next, minishell);
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