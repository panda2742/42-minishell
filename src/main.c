#include "minishell.h"

char	**test_parsing(t_minishell *minishell, char *s)
{
	char	*command_name;
	char	**command_args;
	int		command_argc;

	/* Remplace cette instruction la par ton call de parsing */
	/* TODO */
	command_name = s;
	command_args = ft_split(s, " ");
	command_args++;
	command_argc = 0;
	while (command_args[command_argc])
		command_argc++;

	exec_command(minishell, command_name, command_args, command_argc);
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		**map;
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	if (create_env(env, &minishell.env) == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		show_prompt();
		line = readline(" ");
		map = test_parsing(&minishell, line);
		free(line);
	}
	(void)map;
	return (0);
}
