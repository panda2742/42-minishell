#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define PROJECT_NAME "Minishell"

/**
 * An alias to the unsigned char type, just to set the code more readable.
 */
typedef unsigned char	t_exit;

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
typedef struct s_command
{
	/**
	 * The name of the command.
	 */
	char			*name;
	/**
	 * The argument passed to the command.
	 */
	char			**args;
	/**
	 * The number of arguments passed to the command.
	 */
	int				argc;
	/**
	 * The environment variables of the process.
	 */
	t_env_manager	*env;
	/**
	 * The command exit status. Default on success.
	 */
	t_exit			status;
}					t_command;

/**
 * Represents a prototype of a command function (used for builtins commands).
 * The parameter is a pointer to a s_command structure, defined above.
 */
typedef t_exit (*		t_cmdproto)(t_command *);

/**
 * The main structure of the project/code.
 */
typedef struct s_minishell
{
	t_env_manager	env;
}			t_minishell;

/**
 * Base command which manages the execution process of a command.
 */
t_exit	exec_command(
			t_minishell *minishell,
			char *command_name,
			char **command_args,
			int command_argc
			);

// ENV -----------------------------

t_env	**create_env(char **envp, t_env_manager *env);
void	debug_display_env(t_env_manager *env);
void	free_env(t_env_manager *env);
t_env	*get_var(t_env_manager *env, const char *name);

// ERRORS --------------------------

typedef enum e_error
{
	E_BUILTINS_CD_WARGS,
	E_BUILTINS_CD_NOHOME,
}	t_error;

void	*handle_env_mem_alloc(t_env_manager *env);
char	**error_msgs(void);
void	puterr(t_error err, t_bool is_perror, char *err_arg);

// BUILTINS ------------------------

t_exit	builtins_cd(t_command *c);
t_exit	builtins_echo(t_command *c);
t_exit	builtins_env(t_command *c);
t_exit	builtins_exit(t_command *c);
t_exit	builtins_export(t_command *c);
t_exit	builtins_pwd(t_command	*c);
t_exit	builtins_unset(t_command *c);

#endif