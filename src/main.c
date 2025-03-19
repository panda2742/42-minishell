#include "minishell.h"

char	**test_parsing(t_minishell *minishell, char *s)
{
	char	*command_name;

	/* Remplace cette instruction la par ton call de parsing */
	/* TODO */
	command_name = s;

	exec_command(minishell, command_name, NULL);
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		**map;
	t_minishell	minishell;
	
	(void)argc;
	(void)argv;
	minishell.env.vars = create_env((const char **)env, &minishell.env);
	printf("%p\n", *minishell.env.vars);
	// printf("%p %p %s=%s\n", minishell.env.vars, *minishell.env.vars, (*minishell.env.vars)->name, (*minishell.env.vars)->value);
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

