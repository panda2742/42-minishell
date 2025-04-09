#include "minishell.h"

t_excmd	**exec_test(t_minishell *minishell, char ***envlst)
{
	*envlst = env_to_strlst(&minishell->env);
	t_excmd **res = malloc(sizeof(t_excmd *));

	/*
	Creation d'une commande par défaut
	1. Nom de la commande : ls
	*/
	t_excmd *cmd_a = create_cmd("ls", &minishell->env);
	cmd_a->envp = *envlst;
	/* 
	2. Pour ajouter des arguments, il suffit de remplir argv et de définir argc
	en consequences. Exemple ici avec un split.
	*/
	cmd_a->argv = ft_split("-l -a", " ");
	cmd_a->argc = 2; // on a deux arguments.
	/*
	3. Remplissage du raw.
	*/
	cmd_a->raw = ft_strdup("ls -l -a > out.txt >> out_append1.txt >> out_append2.txt >> out_append3.txt >> out_append4.txt");
	/*
	4. Creation des redirections.

	Dans notre example, on fait 'ls -l -a > out.txt >> out_append1.txt >> out_append2.txt >> out_append3.txt >> out_append4.txt'.
	On crée d'abord les redirect, et on les ajoute a la commande.
	*/
	add_redirect(cmd_a, OUT_REDIR, create_out_redirect("out.txt", false));
	add_redirect(cmd_a, OUT_REDIR, create_out_redirect("out_append1.txt", true));
	add_redirect(cmd_a, OUT_REDIR, create_out_redirect("out_append2.txt", true));
	add_redirect(cmd_a, OUT_REDIR, create_out_redirect("out_append3.txt", true));
	add_redirect(cmd_a, OUT_REDIR, create_out_redirect("out_append4.txt", true));

	/*
	On va créer une autre commande simple pour voir comment ajouter aussi
	des redirections d’entrée.
	*/
	t_excmd *cmd_b = create_cmd("cat", &minishell->env);
	cmd_b->envp = *envlst;
	/*
	On va lui ajouter des redirections en entrée et en sortie. On va
	en gros faire ca : ' << EOF < Makefile cat > out >> out_append'.
	*/
	add_redirect(cmd_b, IN_REDIR, create_heredoc_redirect("EOF"));
	add_redirect(cmd_b, IN_REDIR, create_in_redirect("Makefile"));
	add_redirect(cmd_b, OUT_REDIR, create_out_redirect("out.txt", false));
	add_redirect(cmd_b, OUT_REDIR, create_out_redirect("out_append.txt", true));

	cmd_a->next = cmd_b;
	cmd_b->prev = cmd_a;

	cmd_b->raw = ft_strdup("<< EOF < Makefile cat > out >> out_append");

	res[0] = cmd_a;
	return (res);
}
