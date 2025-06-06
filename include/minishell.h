/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:30 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/19 11:02:23 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <wait.h>
# include <unistd.h>
# include <stdint.h>
# include <dirent.h>
# include <sys/types.h>
# include <stdlib.h>
# include "libft.h"
# include <signal.h>

# ifndef PROJECT_NAME
#  define PROJECT_NAME "Minishell"
# endif

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif
# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif
# define EXIT_PARSING 2
# define EXIT_CANNOT_EXEC 126
# define EXIT_NOT_FOUND 127
# define EXIT_FORK_FAILED 1

# define SIG_NO 0
# define SIG_C 1
# define SIG_C_END 2
# define SIG_HEREDOC 3
# define SIG_HEREDOC_END 4

/**
 * An alias to the int type, just to set the code more readable.
 */
typedef int						t_exit;

/*
 * Parsing
 */
typedef enum e_qtype
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_qtype;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_REDIR_ARG,
	TOKEN_REDIR_ARG_HEREDOC
}	t_token_type;

typedef enum e_redir_type
{
	IN_REDIR,
	OUT_REDIR,
}	t_redir_type;

typedef enum e_error_type
{
	ERR_NONE = 0,
	ERR_MALLOC = -1,
	ERR_LEX = 1,
}	t_err;

/*
 * Exec
 */

typedef enum e_stream_type
{
	STREAM_STD,
	STREAM_PIPE,
	STREAM_REDIR,
}	t_stream_type;

typedef union u_errors
{
	struct
	{
		uint32_t	exc_env_strlst : 1;
		uint32_t	exc_pipe : 1;
		uint32_t	exc_in_last_redir : 1;
		uint32_t	exc_open_fd : 1;
		uint32_t	exc_dup2_in : 1;
		uint32_t	exc_dup2_out : 1;
		uint32_t	exc_dup2_recover_in : 1;
		uint32_t	exc_dup2_recover_out : 1;
		uint32_t	exc_dup_in : 1;
		uint32_t	exc_dup_out : 1;
		uint32_t	exc_fork : 1;
		uint32_t	exc_access_fok : 1;
		uint32_t	exc_access_xok : 1;
		uint32_t	exc_directory : 1;
		uint32_t	exc_execve : 1;
	};
	uint32_t	errors_raw;
}	t_errors;

/*
 * Parsing :
 * First we do t_token, t_tokens are made with fragments
 * Then on expand we do a new list of t_token with the expanded text
 * Then we do a t_token_list with the t_tokens, it stops on pipes and NULL
 */
typedef struct s_fragment
{
	char				*text;
	t_qtype				quote_type;
	struct s_fragment	*next;
}	t_fragment;

typedef struct s_token
{
	t_token_type	type;
	t_fragment		*fragments;
	t_qtype			quote_type;
	char			*text;
	int				index;
	t_bool			is_first_word;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token				*tokens;
	struct s_token_list	*next;
}	t_token_list;

/* Exec */
typedef struct s_env_var
{
	char				*name;
	char				*value;
	size_t				name_length;
	size_t				value_length;
	struct s_env_var	*next;
}	t_env_var;

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
}	t_env_manager;

typedef struct s_streamfd
{
	int				fd;
	t_stream_type	type;
}	t_streamfd;

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
	t_streamfd		fd;
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
	 * Represents the open mode for the outfile. If this boolean is set to true,
	 * it means the file is in append mode. Otherwise, it truncates.
	 */
	t_bool			out_append_mode;
	/**
	 * A pointer to the next file descriptor, used when there is multiple
	 * redirects (for example out1 > out2 > out3 > out4).
	 */
	struct s_redir	*next;
}	t_redir;

typedef struct s_redir_manager
{
	size_t			size;
	t_redir_type	type;
	t_redir			**redirects;
	t_redir			*last;
	t_redir			*problematic;
	t_bool			has_heredoc;
	t_streamfd		final_fd;
}	t_redir_manager;

typedef struct s_strvec
{
	char			*s;
	size_t			len;
	size_t			total_len;
	struct s_strvec	*next;
}	t_strvec;

/**
 * The main structure of the project/code.
 */
typedef struct s_minishell
{
	t_env_manager	env;
	t_exit			last_status;
	int				prompt_theme;
	int				argc;
	char			**argv;
}	t_minishell;

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
	size_t				id;
	/**
	 * The name of the command.
	 */
	char				*name;
	/**
	 * If the command is a builtin, it is not necessarily executed into a
	 * child process. Default to true. // E
	 */
	t_bool				in_a_child;
	/**
	 * The prototype of the command if it is a builtin. Default to NULL. // E
	 */
	t_exit				(*proto)(struct s_excmd *);
	/**
	 * The number of arguments. Default to 0.
	 */
	int					argc;
	/**
	 * The string list of each arguments. Does NOT include the command name.
	 * If empty, the list includes only a NULL element.
	 */
	char				**argv;
	/**
	 * The environment manager. Musts exist. // E
	 */
	t_env_manager		*env;
	/**
	 * The string list of each arguments. Created from the environment managers.
	 * Terminates with a NULL element. If empty, only contains a NULL element.
	 * // E
	 */
	char				**envp;
	/**
	 * The PATH environment variable splitted into a string list, used for the
	 * execve loop. If empty, only contains a NULL element. // E
	 */
	char				**paths;
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
	 * - Writes into: stdout if the last command, s_excmd::pipe[1] otherwise.
	 * // E
	 */
	int					pipe[2];
	/**
	 * If the pipe has been opened or not. // E
	 */
	t_bool				pipe_open[2];
	/**
	 * The stream fd for each standard input and output.
	 */
	t_streamfd			std_dup[2];
	/**
	 * Pipeline variables.
	 */
	struct s_execvars	*vars;
	/**
	 * The previous element of the command list. If it is the first element or
	 * if there is no other element, default value is NULL.
	 */
	struct s_excmd		*prev;
	/**
	 * The next element of the command list. If it is the last element or if
	 * there is no other element, default value is NULL.
	 */
	struct s_excmd		*next;
}	t_excmd;

/**
 * Represents a prototype of a command function (used for builtins commands).
 * The parameter is a pointer to a s_command structure, defined above.
 */

typedef t_exit					(*t_cmdproto)(t_excmd *);

typedef struct s_execvars
{
	size_t		nb_cmd;
	size_t		nb_launched;
	t_excmd		**cmds;
	t_exit		status;
	t_errors	errs;
	t_minishell	*minishell;
}	t_execvars;

typedef struct s_utils
{
	int		i;
	int		j;
	int		k;
	int		len1;
	int		len2;
	char	*s1;
	char	*s2;
}	t_utils;

typedef struct s_word_split
{
	t_token	*new_h;
	t_token	*new_t;
	char	*current;
	t_bool	has_quotes;
}	t_w_split;

typedef struct s_token_list_h
{
	t_token	*current;
	t_token	*start;
	t_token	*end;
}	t_token_list_h;

extern volatile sig_atomic_t	g_last_signal;

// BUILTINS --------------------------------------------------------------------

t_exit			builtin_cd(t_excmd *c);
t_exit			builtin_echo(t_excmd *c);
t_exit			builtin_env(t_excmd *c);
t_exit			builtin_exit(t_excmd *c);
t_exit			builtin_export(t_excmd *c);
t_exit			builtin_pwd(t_excmd *c);
t_exit			builtin_unset(t_excmd *c);
t_bool			display_colors(t_excmd *cmd);
char			*get_identifier(char *str);
unsigned char	get_operation(char *str);
char			*get_value(char *str);
t_bool			valid_identifier_name(char *str);
void			_do_op(t_env_manager *env, char *str);
void			_existing_var_op(t_env_manager *env, char *identifier,
					unsigned char op, char *value);
void			_non_existing_var_op(unsigned char op, t_env_var *var,
					char *value);
t_env_var		*_create_new_var(char *identifier, unsigned char op,
					char *value);

void			_free_everything(t_excmd *cmd, t_execvars *vars, int status,
					t_bool unlink_tmp);
t_bool			_create_pipe_if_necessary(t_excmd *cmd);
void			_child_life(t_execvars *vars, t_excmd *cmd);
t_bool			_error_or_parent_life(int fork_id, t_execvars *vars,
					t_excmd *cmd, pid_t *last_fork);
void			_trigger_waits(t_execvars *vars, pid_t last_fork);
int				_setup_cmd(t_excmd *cmd);
int				_check_input_redir(t_excmd *cmd);
int				_check_output_redir(t_excmd *cmd);
int				_create_input_dup2_redir(t_excmd *cmd);
int				_create_output_dup2_redir(t_excmd *cmd);
t_bool			put_err_status_update(unsigned char *status);

// ENV_MANAGER -----------------------------------------------------------------

t_env_var		**create_env(char **envp, t_env_manager *env);
char			**env_to_strlst(t_env_manager *env);
t_env_var		*get_var(t_env_manager *env, const char *name);
t_env_var		**dup_env_vars(t_env_manager *env);
void			free_dup_vars(t_env_var **vars);

// ERRORS ----------------------------------------------------------------------

void			puterr(char *message, t_bool call_perror);
void			putwarn(char *message, t_bool call_perror);

// EXEC ------------------------------------------------------------------------

t_exit			heredoc(char *del, char **filepath, t_bool skip_writing);
t_excmd			*create_cmd(char *cmd_name, t_env_manager *env);
t_redir			*free_redir_and_return_null(t_redir *redirect);
void			update_last_next(t_redir **last, t_redir *redirect);
t_excmd			*free_res_return_null(t_excmd *res);
t_redir			*add_redirect(t_excmd *cmd, t_redir_type type,
					t_redir *redirect);
t_redir			*create_in_redirect(char *filepath);
t_redir			*create_out_redirect(char *filepath, t_bool append_mode);
t_redir			*create_heredoc_redirect(char *delimiter);
void			clear_every_tmpfile(t_excmd **cmds);
t_redir			*get_last_redirect(t_redir_manager *redirects_manager);
t_execvars		*exec_command(t_minishell *minishell, t_excmd **cmds);
t_cmdproto		load_builtin(const char *command_name, t_cmdproto *proto);
void			exec_single_builtin(t_excmd *cmd);
char			*get_full_path(char *path, char *cmd_name);
void			execute_from_path(t_excmd *cmd, size_t redir_size);
t_execvars		*create_execvars(t_minishell *minishell, t_excmd **cmds);
void			reset_execvars(t_execvars *vars);
void			exec_multiple_commands(t_execvars *vars);
int				close_pipe(t_excmd *cmd, int streams);
t_env_var		*ensure_var(t_env_manager *env, const char *name,
					char *default_val);
t_env_var		*init_var(t_env_manager *env, const char *name);
void			init_all_vars(t_env_manager *env, char **envp, t_env_var *elt,
					size_t i);
t_bool			load_env_strlst(t_execvars *vars);
t_redir			*mem_redir_fail(t_redir_manager *redirects_manager,
					t_redir *last);
t_bool			var_exists(t_env_manager *env, char *name);
void			print_core_dumped_and_st(t_execvars *vars);

// MEMORY ----------------------------------------------------------------------

void			free_cmds(t_excmd **cmds);
void			free_one_cmd(t_excmd *cmd);
void			free_env(t_env_manager *env);
void			sort_env_list(t_env_var **head_ref);

// MISC ------------------------------------------------------------------------

char			*show_prompt(t_minishell *minishell);
void			init_sighandler(void);
void			init_sighandler_heredoc(void);
void			sigint_handler(int sig);
void			sigint_heredoc(int sig);
void			check_sigint(t_minishell *mini);
char			*build_theme0(const char *user, const char *path);
char			*build_theme1(int last_status, const char *user,
					const char *path);
char			*build_theme2(int last_status, const char *path);
char			*get_random_chars(uint8_t n);

// PARSING ---------------------------------------------------------------------

// CMD ------------------------------------------------------------------------
t_excmd			*create_cmd_list(t_token_list *token_list_head,
					t_minishell *minishell);

// LEXER ----------------------------------------------------------------------

t_err			parse_quote_prefixed_fragment(t_token *token,
					const char *input, int *i);
int				parse_single_quote(t_token *token, const char *input, int *i);
int				parse_double_quote(t_token *token, const char *input, int *i);
int				parse_unquoted(t_token *token, const char *input, int *i);

t_err			handle_redir_pipe(int *i, t_token **token_list,
					const char *input);
t_token			*add_new_token(t_token **new_h, t_token **new_t,
					char *current, t_token *token);
t_err			process_unquoted_frag(const char *expanded, char **current,
					t_w_split **new_list, t_token *token);
void			update_token_redir(t_token *list);
int				lexer_parse(t_token *token);
int				is_char_redir_or_pipe(char c);
void			print_tokens(t_token *tokens);
t_err			ft_input(const char *input, t_token **output);

char			*expand_fragment(const char *input, int quote,
					t_minishell *mini);
t_qtype			set_qtype_fragment(t_token *token_head);
t_fragment		*new_fragment(const char *start, size_t len,
					t_qtype quote_type);
void			append_fragment(t_token *token, t_fragment *frag);
void			free_tokens(t_token *tokens);
t_token			*ft_create_token(t_token_type type);
void			append_token(t_token **token_list, t_token *token);
void			free_tokens_in_list(t_token_list *head);
t_token_list	*add_token_list_node(t_token_list_h *u,
					t_token_list **head_list);	
void			token_list(t_token *head_token, t_token_list **head_list,
					t_minishell *mini);
// TOKENIZER
void			expand_caller(t_token *token, t_token **new_tokens,
					t_minishell *minishell);
void			split_error(t_token *token, t_minishell *mini, t_err status,
					t_token **new_tokens);
t_token			*get_tail(t_token *tok);
t_err			empty_var(t_w_split *n_list, t_token **out_list);
t_err			set_n_list_and_frag(t_w_split *n_list);
t_err			free_n_list(t_w_split *n_list);

t_qtype			set_qtype_fragment(t_token *token_head);
void			update_head_and_last(t_token **new_h, t_token **new_t,
					t_token *new_token);
t_err			handle_last_rvalue(t_minishell *mini, t_utils *utils);
void			set_var_name(t_utils *utils, char *var_name, char *input);
t_err			handle_expand_char(t_utils *utils, t_minishell *mini,
					char *input);
void			free_tokens_list(t_token *tokens);
void			free_tokens_in_list(t_token_list *head);
void			update_head_tail(t_token_list_h *utils, t_token **new_token,
					t_token **tmp);
void			append_cmd_node(t_token_list **head, t_token_list *node);
void			exit_node_failed(t_minishell *mini, t_token_list **tok_cmd_h,
					t_token *tok_exp_h);
t_token_list	*add_token_failed(t_token_list *list, t_token *new_token);
void			set_values(t_token_list_h *utils);

// UTILS -----------------------------------------------------------------------

size_t			_int_size(int n);

// MAIN_UTILS
void			create_env_or_exit_if_env_error(char **env,
					t_minishell *minishell, int argc, char **argv);
void			exit_if_line_null(char *line, t_minishell *minishell);
t_excmd			*handle_status_err(t_err status, t_token *token,
					t_minishell *mini);

// PARSING
size_t			count_arg_words(t_token *token);
char			*free_str_return_null(char *str);
t_err			handle_normal_char(t_utils *utils, char *input);
t_err			add_char_to_string(char *expanded, char **current, int *i);
char			**ft_split_a(char const *s, char c);
char			*str_join_free(char *s1, const char *s2);
int				ft_strcmp(char *s1, char *s2);
char			*get_first_word(t_token *token);
int				handle_is_redir_tokens(t_excmd *cmd, t_token *token);
void			incr_on_alnum(char *str, int *j, int i);
char			*ft_sprintf(const char *format, ...);
void			*empty_tab(void);
char			**empty_paths(void);
int				is_redir(t_token *head_token);
void			print_token_list(t_token_list *list);
void			skip_spaces(const char *input, int *i);
size_t			token_lstsize(t_token *head);

#endif