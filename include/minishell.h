#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <wait.h>
# include "libft.h"

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
	char		**envlst;
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
	char			*filepath;
	/**
	 * The file descriptor, given when the file is open. STD[IN/OUT]_FILENO
	 * as default.
	 */
	int				fd;
	/**
	 * If it includes an Here Document, this boolean is set to true. Otherwise
	 * it is set to false.
	 */
	t_bool			is_heredoc;
	/**
	 * The id of the heredoc.
	 */
	size_t			heredoc_id;
	/**
	 * The delimiter used for a Here Document. Set to NULL as default. 
	 */
	char			*heredoc_del;
	/**
	 * If there is an Here Document, the content is firstly written into the
	 * memory, and then put into a pipe's output file descriptor when it has to 
	 * be used. Set to NULL as default.
	 */
	char			*heredoc_content;
	/**
	 * Represents the open mode for the outfile. If this boolean is set to true,
	 * it means the file is in append mode. Otherwise, it truncates.
	 */
	t_bool			out_append_mode;
	/**
	 * A pointer to the next file descriptor, used when there is multiple
	 * redirects (for example out1 > out2 > out3 > out4).
	 */
	struct s_redir	*next;
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
	t_redir			*last;
	t_redir			*problematic;
	t_bool			has_heredoc;
	int				final_fd;
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
	 * The id of the command (executed in the order). // E
	 */
	size_t			id;
	/**
	 * The name of the command. 
	 */
	char			*name;
	/**
	 * If the command is a builtin, it is not necessarily executed into a
	 * child process. Default to true. // E
	 */
	t_bool			in_a_child;
	/**
	 * The prototype of the command if it is a builtin. Default to NULL. // E
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
	 * The environment manager. Musts exist. // E
	 */
	t_env_manager	*env;
	/**
	 * The string list of each arguments. Created from the environment managers.
	 * Terminates with a NULL element. If empty, only contains a NULL element. // E
	 */
	char			**envp;
	/**
	 * The raw string of the command. It includes every arguments, as it was
	 * written in the prompt. It includes a copy of the command name as default.
	 */
	char			*raw;
	/**
	 * The PATH environment variable splitted into a string list, used for the
	 * execve loop. If empty, only contains a NULL element. // E
	 */
	char			**paths;
	/**
	 * The successive input stream file descriptors. Per default, set the
	 * file descriptor to STDIN_FILENO. // E
	 */
	t_redir_manager		in_redirects;
	/**
	 * The successive input stream file descriptors. Per default, set the
	 * file descriptor to STDOUT_FILENO. //E
	 */
	t_redir_manager		out_redirects;
	/**
	 * @brief The pipe of the command. Creates a stream between the input and
	 * the output of the command.
	 * 
	 * How does it work? The scenario that occur is:
	 * - The command is instanced, the pipe is created.
	 * - Reads: stdin if first command, s_excmd::pipe[0] otherwise.
	 * - Writes into: stdout if the last command, s_excmd::pipe[1] otherwise. // E
	 */
	int				pipe[2];
	/**
	 * If the pipe has been opened or not. // E
	 */
	t_bool			pipe_open;
	/**
	 * The status of the executed command. // E
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
	size_t	nb_launched;
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

typedef enum e_qtype
{
	NONE,
	SINGLE,
	DOUBLE
}						t_qtype;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	REDIR_ARG
}						t_token_type;

typedef struct s_fragment
{
	char				*text;
	t_qtype				quote_type;
	struct s_fragment	*next;
}						t_fragment;

typedef struct s_token
{
	t_token_type		type;
	t_fragment			*fragments;
	t_qtype				quote_type;
	char				*text;
	int					index;
	struct s_token		*next;
}						t_token;

typedef struct s_token_list
{
	t_token				*tokens;
	struct s_token_list *next;
}						t_token_list;

// typedef struct s_token_exp
// {
// 	char				*str;
// 	struct s_token_exp	*next;
// }						t_token_exp;

// typedef struct s_redir
// {
// 	int					type;
// 	char				*filename;
// 	int					quote_type;
// 	struct s_redir		*next;
// }						t_redir;

// typedef struct s_word
// {
// 	int					quote_type;
// 	char				*word;
// 	struct s_word		*next;
// }						t_word;

// typedef struct s_cmds
// {
// 	t_word				*words;
// 	t_redir				*redir;
// 	int					leak_flag;
// 	struct s_cmds		*next;
// }						t_cmds;

# ifndef PROJECT_NAME
#  define PROJECT_NAME "Minishell"
# endif


typedef struct s_utils
{
	int					i;
	int					j;
	int					k;
	int					len1;
	int					len2;
	char				*s1;
	char				*s2;
}						t_utils;

// utiles parser
size_t					count_arg_words(t_token *token);
char					*free_str_return_null(char *str);
char					**ft_split_a(char const *s, char c);
char					*str_join_free(char *s1, const char *s2);
int						ft_strcmp(char *s1, char *s2);
int						is_redir(t_token *head_token); // return 1 si c est une redir
void					print_token_list(t_token_list *list);
void					skip_spaces(const char *input, int *i);
void					del_cmds(void *content);
void					del_redir(void *content);
size_t					token_lstsize(t_token *head);
void					del_word(void *content);

// Arg
// t_excmd					*cmd_to_arg(t_cmds *head);

// Expand_tokens
char					*expand_token(t_token *token, t_env_manager *env);
t_token					*word_split_token(t_token *token, t_env_manager *env);

// Fragment
t_fragment				*new_fragment(const char *start, size_t len,
							t_qtype quote_type);
void					append_fragment(t_token *token, t_fragment *frag);

// free str return null

// ft_cmd_list_size
// int						ft_cmd_lstsize(t_word *cmd);

// Lexer
t_token					*ft_input(const char *input);
void					print_tokens(t_token *tokens);
t_token					*ft_create_token(t_token_type type);
void					free_tokens(t_token *tokens);
char					*token_to_string(t_token *token,
							t_minishell *minishell);

// Token lexer
void					append_token(t_token **token_list, t_token *token);

// Token list
void	token_list(t_token *head_token, t_token_list **head_list);
void	free_tokens_in_list(t_token *tokens, t_token_list *list);

// Lexer parser
int						lexer_parse(t_token *token);
int						ft_strcmp(char *s1, char *s2);

// Signals
void					set_sig_action(void);
void					sigint_handler(int signal);

// Parser
int						parser(t_token *head, t_minishell *minishell);

// Redir parsing
// void					create_redir(t_cmds *cmd, t_token *head,
// 							t_minishell *minishell);

// Utils parser
const char	*get_token_type_str(t_token_type type);
		// pour print les noms des redir

// Utils lexer
int						is_separator(char c);
int						is_char_redir_or_pipe(char c);

// Utils 1
void					*get_next_word(void *node);
void					*get_next_redir(void *node);
void					lst_clear(void **lst, void *(*get_next)(void *),
							void (*del)(void *));

// Get next token
void					*get_next_token(void *node);
void					*get_next_cmds(void *node);
void					*get_next_word(void *node);
void					*get_next_redir(void *node);

// To delete later
// void					print_elements_cmds(t_word *head_w, t_redir *head_r);

t_cmdproto	load_builtin(const char *command_name, t_cmdproto *proto);
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
void	free_one_cmd(t_excmd *cmd);

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

t_excmd	**exec_test(t_minishell *minishell);
void	link_commands(t_excmd *cmd1, t_excmd *cmd2);
void	print_cmds(t_excmd *cmd);
void	print_cmd(t_excmd *cmd);

# endif
