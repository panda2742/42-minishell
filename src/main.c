#include "minishell.h"

char	**test_parsing(t_minishell *minishell, char *s)
{
	char	*command_name;
	char	*arg_str;
	char	**command_args;
	int		command_argc;

	/* Remplace cette instruction la par ton call de parsing */
	/* TODO */
	command_args = ft_split(s, " ");
	arg_str = ft_strchr(s, ' ') + 1;
	command_name = command_args[0];
	command_argc = 0;
	while (command_args[command_argc])
		command_argc++;

	(void)minishell;
	ft_free_strtab(command_args);
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		*prompt;
	char		**map;
	t_minishell	minishell;

	if (create_env(env, &minishell.env) == NULL)
		return (EXIT_FAILURE);
	char **envlst = NULL;
	t_excmd	**tests = exec_test(&minishell, &envlst);
	exec_command(&minishell, tests);
	free_env(&minishell.env);
	ft_free_strtab(envlst);
	free_cmds(tests);
	// (void)argc;
	// (void)argv;
	// (void)env;
	// while (1)
	// {
	// 	prompt = show_prompt(&minishell.env);
	// 	line = readline(prompt);
	// 	free(prompt);
	// 	map = test_parsing(&minishell, line);
	// 	free(line);
	// }
	(void)prompt;
	(void)line;
	(void)argc;
	(void)argv;
	(void)map;
	return (0);
}
