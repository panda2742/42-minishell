
#include "minishell.h"

void	print_elements_cmds(t_word *head_w, t_redir *head_r)
{
	t_word *tmp_w;
	t_redir *tmp_r;
	tmp_w = head_w;
	while (tmp_w != NULL)
	{
		ft_printf("Create word: %s quote_type %i\n", tmp_w->word,
			tmp_w->quote_type);
		tmp_w = tmp_w->next;
	}
	tmp_r = head_r;
	while (tmp_r != NULL)
	{
		ft_printf("Create redir: type %s | value: %s | quote_type %i\n",
			get_token_type_str(tmp_r->type), tmp_r->filename,
			tmp_r->quote_type);
		tmp_r = tmp_r->next;
	}
}
