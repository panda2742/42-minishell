#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/**
 * An alias to the unsigned char type, just to set the code more readable.
 */
typedef unsigned char t_exit;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_env_manager
{
	/**
	 * Containing all the environment variables, duplicated in a linked list.
	 * You can edit, delete or add some and everything will be fine.
	 */
	t_env	**vars;
	/**
	 * The amount of environment variables.
	 */
	size_t	env_size;
}			t_env_manager;

/**
 * @brief A command data structure.
 * The base structure of a command data. Those data is passed for example when
 * you call the function for a builtin command.
 */
typedef struct s_command {
	/**
	 * The name of the command.
	 */
	char			*name;
	/**
	 * The argument passed to the command.
	 */
	char			**args;
	/**
	 * The environment variables of the process.
	 */
	t_env_manager	*env;
}			t_command;

/**
 * Represents a prototype of a command function (used for builtins commands).
 * The parameter is a pointer to a s_command structure, defined above.
 */
typedef t_exit (* command_prototype)(t_command *);

/**
 * The main structure of the project/code.
 */
typedef struct	s_minishell
{
	t_env_manager	env;
}			t_minishell;

/**
 * Base command which manages the execution process of a command.
 */
t_exit	exec_command(t_minishell *minishell, const char *command_name, const char **command_args);

/** 
 * Simply display the base prompt with readline.
 */
void	show_prompt(void);

// ENV -----------------------------

t_env	**create_env(const char **envp, t_env_manager *env);
char	**env_str(t_env_manager *env);

// BUILTINS ------------------------

t_exit	builtins_cd(t_command *c);
t_exit	builtins_echo(t_command *c);
t_exit	builtins_env(t_command *c);
t_exit	builtins_exit(t_command *c);
t_exit	builtins_export(t_command *c);
t_exit	builtins_pwd(t_command	*c);
t_exit	builtins_unset(t_command *c);

#endif