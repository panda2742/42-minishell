#include "minishell.h"

t_excmd	*create_cmd(char *cmd_name, t_env_manager *env)
{
	t_excmd	*res;

	res = malloc(sizeof(t_excmd));
	if (!res)
		return (NULL);
	res->_id = -1;
	res->name = cmd_name;
	res->in_a_child = false;
	res->proto = NULL;
	res->argc = 0;
	res->argv = empty_tab();
	res->env = env;
	res->envp = NULL;
	res->raw = cmd_name;
	res->paths = empty_tab();
	res->in_redirects.size = 0;
	res->in_redirects.redirects = NULL;
	res->in_redirects.type = IN_REDIR;
	res->out_redirects.size = 0;
	res->out_redirects.redirects = NULL;
	res->out_redirects.type = OUT_REDIR;
	res->status = EXIT_SUCCESS;
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

t_redir	*add_redirect(t_excmd *cmd, t_redir_type type, t_redir *redirect)
{
	t_redir_manager	*manager;
	t_redir			*last;

	manager = &cmd->in_redirects;
	if (type == OUT_REDIR)
		manager = &cmd->out_redirects;
	if (manager->size == 0)
	{
		manager->redirects = malloc(sizeof(t_redir *));
		if (!manager->redirects)
			return (NULL);
		manager->redirects[0] = redirect;
		return (redirect);
	}
	last = *manager->redirects;
	while (last->next)
		last = last->next;
	last->next = redirect;
	manager->size += 1;
	return (redirect);
}

t_redir	*create_in_redirect(char *filepath)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	if (!res)
		return (NULL);
	res->filepath = filepath;
	res->fd = STDIN_FILENO;
	res->is_heredoc = false;
	res->heredoc_id = -1;
	res->heredoc_del = NULL;
	res->heredoc_content = NULL;
	res->out_append_mode = false;
	res->next = NULL;
	return (res);
}

t_redir	*create_out_redirect(char *filepath, t_bool append_mode)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	if (!res)
		return (NULL);
	res->filepath = filepath;
	res->fd = STDOUT_FILENO;
	res->is_heredoc = false;
	res->heredoc_id = -1;
	res->heredoc_del = NULL;
	res->heredoc_content = NULL;
	res->out_append_mode = append_mode;
	res->next = NULL;
	return (res);
}

t_redir	*create_heredoc_redirect(char *delimiter)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	if (!res)
		return (NULL);
	res->filepath = NULL;
	res->fd = -1;
	res->is_heredoc = true;
	res->heredoc_id = -1;
	res->heredoc_del = delimiter;
	res->heredoc_content = NULL;
	res->out_append_mode = false;
	res->next = NULL;
}

