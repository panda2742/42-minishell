#include "minishell.h"

static t_excmd	*_cat_cat_ls(t_minishell *minishell)
{
	t_excmd	*cat1 = create_cmd("cat", &minishell->env);
	t_excmd	*cat2 = create_cmd("cat", &minishell->env);
	t_excmd	*ls = create_cmd("ls", &minishell->env);

	link_commands(cat1, cat2);
	link_commands(cat2, ls);

	return (cat1);
}

static t_excmd	*_cat_urandom_head(t_minishell *minishell)
{
	t_excmd *cat = create_cmd("cat", &minishell->env);
	t_excmd *head = create_cmd("head", &minishell->env);

	add_redirect(cat, IN_REDIR, create_in_redirect("/dev/urandom"));

	link_commands(cat, head);

	return (cat);
}

static t_excmd	*_casual_test(t_minishell *minishell)
{
	t_excmd *cat = create_cmd("env", &minishell->env);

	add_redirect(cat, IN_REDIR, create_in_redirect("Makefile"));

	return (cat);
}

static t_excmd	*_complete_test_1(t_minishell *minishell)
{
	t_excmd *cat1 = create_cmd("cat", &minishell->env);

	add_redirect(cat1, IN_REDIR, create_in_redirect("Makefile"));

	cat1->argc = 1;
	cat1->argv = ft_split("-e", "");

	return (cat1);
}

t_excmd	**exec_test(t_minishell *minishell)
{
	t_excmd **res = malloc(sizeof(t_excmd *));

	(void)_cat_cat_ls;
	(void)_cat_urandom_head;
	(void)_casual_test;
	(void)_complete_test_1;
	res[0] = _complete_test_1(minishell);
	return (res);
}
