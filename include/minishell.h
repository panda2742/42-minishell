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
 * Represents a prototype of a command function (used for builtins commands).
 * The parameter is a pointer to a s_command structure, defined above.
 */

typedef struct s_excmd
{
	char			*name;
	t_bool			is_builtin;
	t_bool			in_a_child;
	t_exit 			(*proto)(struct s_excmd *);
	int				argc;
	char			**argv;
	t_env_manager	*env;
	char			**envp;
	char			*raw;
	char			**paths;
	t_bool			has_heredoc;
	char			*heredoc_del;
	char			*heredoc_content;
	char			*infile;
	int				in_fd;
	char			*outfile;
	int				out_fd;
	int				pipe[2];
	t_exit			status;
	struct s_excmd	*prev;
	struct s_excmd	*next;
}					t_excmd;

typedef t_exit (*		t_cmdproto)(t_excmd *);

/**
 * The main structure of the project/code.
 */
typedef struct s_minishell
{
	t_env_manager	env;
}			t_minishell;

t_cmdproto	*load_builtin(const char *command_name, t_cmdproto *proto);
t_exit	heredoc(char *del, char *buffer);

// ENV -----------------------------

t_env	**create_env(char **envp, t_env_manager *env);
void	debug_display_env(t_env_manager *env);
void	free_env(t_env_manager *env);
t_env	*get_var(t_env_manager *env, const char *name);

// ERRORS --------------------------

void	*handle_env_mem_alloc(t_env_manager *env);
void	puterr(char *message, t_bool call_perror);
t_exit	command_failure(t_excmd *c, char *message, t_bool call_perror);

// BUILTINS ------------------------

t_exit	builtins_cd(t_excmd *c);
t_exit	builtins_echo(t_excmd *c);
t_exit	builtins_env(t_excmd *c);
t_exit	builtins_exit(t_excmd *c);
t_exit	builtins_export(t_excmd *c);
t_exit	builtins_pwd(t_excmd	*c);
t_exit	builtins_unset(t_excmd *c);

// PROMPT --------------------------

char	*show_prompt(t_env_manager *env);

// UTILS ---------------------------

char	*ft_sprintf(const char *format, ...);

#endif