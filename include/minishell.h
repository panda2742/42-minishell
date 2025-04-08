#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft.h"

# ifndef PROJECT_NAME
#  define PROJECT_NAME "Minishell"
# endif

/**
 * An alias to the unsigned char type, just to set the code more readable.
 */
typedef unsigned char	t_exit;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	size_t				name_length;
	size_t				value_length;
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_env_manager
{
	/**
	 * Containing all the environment variables, duplicated in a linked list.
	 * You can edit, delete or add some and everything will be fine.
	 */
	t_env_var	**vars;
	/**
	 * The amount of environment variables.
	 */
	size_t		env_size;
}			t_env_manager;

/**
 * Represents a structure for a file descriptor. Include its path and then its
 * file descriptor once it is open.
 */
typedef struct s_redir
{
	/**
	 * The path of the file (absolute or relative). NULL if not set.
	 */
	char		*filepath;
	/**
	 * The file descriptor, given when the file is open. STD[IN/OUT]_FILENO
	 * as default.
	 */
	int			fd;
	/**
	 * If it includes an Here Document, this boolean is set to true. Otherwise
	 * it is set to false.
	 */
	t_bool		is_heredoc;
	/**
	 * The id of the heredoc.
	 */
	size_t		heredoc_id;
	/**
	 * The delimiter used for a Here Document. Set to NULL as default. 
	 */
	char		*heredoc_del;
	/**
	 * If there is an Here Document, the content is firstly written into the
	 * memory, and then put into a pipe's output file descriptor when it has to 
	 * be used. Set to NULL as default.
	 */
	char		*heredoc_content;
	/**
	 * Represents the open mode for the outfile. If this boolean is set to true,
	 * it means the file is in append mode. Otherwise, it truncates.
	 */
	t_bool		out_append_mode;
	/**
	 * A pointer to the next file descriptor, used when there is multiple
	 * redirects (for example out1 > out2 > out3 > out4).
	 */
	struct s_fd	*next;
}				t_redir;

typedef enum e_redir_type
{
	IN_REDIR,
	OUT_REDIR,
}	t_redir_type;

typedef struct s_redir_manager
{
	size_t			size;
	t_redir_type	type;
	t_redir			**redirects;
}			t_redir_manager;

/**
 * @brief The data of a command executed in the execution program.
 * 
 * The data of a command executed in the execution program. It is a linked list
 * who contains all the required informations, like pipes, heredoc, etc.
 */
typedef struct s_excmd
{
	/**
	 * The id of the command (executed in the order);
	 */
	size_t			_id;
	/**
	 * The name of the command.
	 */
	char			*name;
	/**
	 * If the command is a builtin, it is not necessarily executed into a
	 * child process. Default to true.
	 */
	t_bool			in_a_child;
	/**
	 * The prototype of the command if it is a builtin. Default to NULL.
	 */
	t_exit 			(*proto)(struct s_excmd *);
	/**
	 * The number of arguments. Default to 0.
	 */
	int				argc;
	/**
	 * The string list of each arguments. Does NOT include the command name.
	 * If empty, the list includes only a NULL element.
	 */
	char			**argv;
	/**
	 * The environment manager. Musts exist.
	 */
	t_env_manager	*env;
	/**
	 * The string list of each arguments. Created from the environment managers.
	 * Terminates with a NULL element. If empty, only contains a NULL element.
	 */
	char			**envp;
	/**
	 * The raw string of the command. It includes every arguments, as it was
	 * written in the prompt. It includes a copy of the command name as default.
	 */
	char			*raw;
	/**
	 * The PATH environment variable splitted into a string list, used for the
	 * execve loop. If empty, only contains a NULL element.
	 */
	char			**paths;
	/**
	 * The successive input stream file descriptors. Per default, set the
	 * file descriptor to STDIN_FILENO.
	 */
	t_redir_manager		in_redirects;
	/**
	 * The successive input stream file descriptors. Per default, set the
	 * file descriptor to STDOUT_FILENO.
	 */
	t_redir_manager		out_redirects;
	/**
	 * @brief The pipe of the command. Creates a stream between the input and
	 * the output of the command.
	 * 
	 * How does it work? The scenario that occur is:
	 * - The command is instanced, the pipe is created.
	 * - Reads: stdin if first command, s_excmd::pipe[0] otherwise.
	 * - Writes into: stdout if the last command, s_excmd::pipe[1] otherwise.
	 */
	int				pipe[2];
	/**
	 * The status of the executed command.
	 */
	t_exit			status;
	/**
	 * The previous element of the command list. If it is the first element or 
	 * if there is no other element, default value is NULL.
	 */
	struct s_excmd	*prev;
	/**
	 * The next element of the command list. If it is the last element or if
	 * there is no other element, default value is NULL.
	 */
	struct s_excmd	*next;
}					t_excmd;

typedef struct s_execparams
{
	size_t	nb_cmd;
	t_excmd	**cmds;
}			t_execparams;

typedef struct s_strvec
{
	char			*s;
	size_t			len;
	size_t			total_len;
	struct s_strvec	*next;
}					t_strvec;

/**
 * Represents a prototype of a command function (used for builtins commands).
 * The parameter is a pointer to a s_command structure, defined above.
 */
typedef t_exit (*		t_cmdproto)(t_excmd *);

/**
 * The main structure of the project/code.
 */
typedef struct s_minishell
{
	t_env_manager	env;
	t_exit			last_status;
}			t_minishell;

t_cmdproto	*load_builtin(const char *command_name, t_cmdproto *proto);
t_exit		heredoc(char *del, char *buffer, t_bool skip_writing);

// ENV -----------------------------

t_env_var	**create_env(char **envp, t_env_manager *env);
char		**env_to_strlst(t_env_manager *env);
void		free_env(t_env_manager *env);
t_env_var	*get_var(t_env_manager *env, const char *name);

// ERRORS --------------------------

void	*handle_env_mem_alloc(t_env_manager *env);
void	puterr(char *message, t_bool call_perror);
t_exit	command_failure(t_excmd *c, char *message, t_bool call_perror);

// EXEC ----------------------------

t_exit	launch_process(t_excmd *cmd);
t_exit	exec_command(t_minishell *minishell, t_excmd **cmds);
void	free_cmds(t_excmd **cmds);
t_excmd	*create_cmd(char *cmd_name, t_env_manager *env);
t_redir	*get_last_redirect(t_redir_manager *redirects_manager);

// FILE DESCRIPTORS ----------------

t_redir	*add_redirect(t_excmd *cmd, t_redir_type type, t_redir *redirect);
t_redir	*create_in_redirect(char *filepath);
t_redir	*create_out_redirect(char *filepath, t_bool append_mode);
t_redir	*create_heredoc_redirect(char *delimiter);

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
void	*empty_tab(void);

// TESTS ---------------------------

t_excmd	**exec_test(t_minishell *minishell, char ***envlst);

#endif