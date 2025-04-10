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
	cmd_a->raw = ft_strdup("");
	/*
	4. Creation des redirections.
	*/
	// add_redirect(cmd_a, IN_REDIR, create_heredoc_redirect("EOF"));
	add_redirect(cmd_a, OUT_REDIR, create_heredoc_redirect("EOF"));
	add_redirect(cmd_a, OUT_REDIR, create_out_redirect("out1", false));
	add_redirect(cmd_a, OUT_REDIR, create_out_redirect("out2", false));

	res[0] = cmd_a;
	return (res);
}
