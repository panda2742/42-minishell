#include "minishell.h"

static void	_create_env(t_minishell *minishell, char **env);

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
	_create_env(&minishell, env);
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

static void	_create_env(t_minishell *minishell, char **env)
{
	size_t	env_size;
	size_t	i;
	size_t	env_var_len;

	env_size = 0;
	while (env[env_size])
		env_size++;
	minishell->env = malloc(sizeof(char *) * (env_size + 1));
	if (!minishell->env)
		return ;
	minishell->env[env_size] = 0;
	i = -1;
	while (++i < env_size)
	{
		env_var_len = ft_strlen(env[i]);
		minishell->env[i] = malloc(sizeof(char) * (env_var_len + 1));
		if (!minishell->env)
			ft_free_strtab(minishell->env);
		ft_strlcpy(minishell->env[i], env[i], env_var_len);
	}
}
