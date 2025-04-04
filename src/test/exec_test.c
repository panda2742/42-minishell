#include "minishell.h"

t_excmd	**exec_test(t_minishell *minishell, char ***envlst)
{
	t_excmd **t = malloc(sizeof(t_excmd *));
	*envlst = env_to_strlst(&minishell->env);
	int i;

	// ls -l -a | cat Makefile

	// ls -l -a
	t_excmd *l1 = malloc(sizeof(t_excmd));
	l1->name = ft_strdup("ls");
	l1->argv = ft_split("-l -a", " ");
	i = 0;
	while (l1->argv[i])
		i++;
	l1->argc = i;
	l1->env = &minishell->env;
	l1->envp = *envlst;
	l1->raw = ft_strdup("ls -l -a");
	l1->has_heredoc = false;
	l1->infile = NULL;
	l1->outfile = NULL;

	// cat Makefile
	t_excmd *l2 = malloc(sizeof(t_excmd));
	l2->name = ft_strdup("cat");
	l2->argv = ft_split("Makefile", " ");
	i = 0;
	while (l2->argv[i])
		i++;
	l2->argc = i;
	l2->env = &minishell->env;
	l2->envp = *envlst;
	l2->raw = ft_strdup("cat Makefile");
	l2->has_heredoc = false;
	l2->infile = NULL;
	l2->outfile = NULL;

	l1->next = l2;
	l1->prev = NULL;
	l2->next = NULL;
	l2->prev = l1;

	t[0] = l1;
	return (t);
}
