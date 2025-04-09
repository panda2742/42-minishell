/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:32:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/08 14:34:10 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"

typedef enum e_qtype
{
	NONE,
	SINGLE,
	DOUBLE
}	t_qtype;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	REDIR_ARG
} t_token_type;

typedef struct s_fragment
{
	char				*text;
	t_qtype				quote_type;
	struct	s_fragment 	*next;
} t_fragment;


typedef struct s_token
{
	t_token_type 	type;
	t_fragment 		*fragments;
	int 			index;
	struct s_token *next;
} t_token;

typedef struct s_token_exp {
    char                *str;
    struct s_token_exp  *next;
} t_token_exp;

typedef struct s_redir
{
	int 			type;
	char 			*filename;
	int 			quote_type;
	struct s_redir 	*next;
} t_redir;

typedef struct s_word
{
	int 			quote_type;
	char 			*word;
	struct s_word 	*next;
} t_word;

typedef struct s_cmds
{
	t_word 			*words;
	t_redir 		*redir;
	int 			leak_flag;
	struct s_cmds 	*next;
} t_cmds;

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
	size_t	env_size;
}			t_env_manager;


typedef struct s_minishell
{
	t_env_manager	env;
}			t_minishell;


// $VAR
typedef unsigned char	t_exit;

typedef struct s_excmd
{
	/**
	 * The name of the command.
	 */
	char			*name;
	/**
	 * If it is a builtin command or not. Default to false.
	 */
	t_bool			is_builtin;
	/**
	 * If the command is a builtin, it is not necessarely executed into a
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
	 * If it includes an Here Document, this boolean is set to true. Otherwise
	 * it is set to false.
	 */
	t_bool			has_heredoc;
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
	 * The input file if a '<' redirect is specified. Set to NULL as default.
	 */
	char			*infile;
	/**
	 * The file descriptor for the input file, if there is one. Set to 0 as
	 * default.
	 */
	int				in_fd;
	/**
	 * The output file if a '>' redirect is specified. Set to NULL as default.
	 */
	char			*outfile;
	/**
	 * The file descriptor for the ouput filem if there is one. Set to 1 as
	 * default.
	 */
	int				out_fd;
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

typedef t_exit (*		t_cmdproto)(t_excmd *);

// Arg
t_excmd	*cmd_to_arg(t_cmds *head);

// Expand_tokens
char *expand_token(t_token *token, t_env_manager *env);
t_token *word_split_token(t_token *token, t_env_manager *env);
char *str_join_free(char *s1, const char *s2);

// Fragment 
t_fragment *new_fragment(const char *start, size_t len, t_qtype quote_type);
void	append_fragment(t_token *token, t_fragment *frag);

// ft_cmd_list_size
int	ft_cmd_lstsize(t_word *cmd);

// Ft_split_parser.c
char	**ft_split_a(char const *s, char c);

// Lexer
t_token	*ft_input(const char *input);
void	print_tokens(t_token *tokens);
t_token *ft_create_token(t_token_type type);
void	free_tokens(t_token *tokens);
char *token_to_string(t_token *token, t_minishell *minishell);


// Get var
t_env_var	*get_var(t_env_manager *env, const char *name);
t_env_var	**create_env(char **envp, t_env_manager *env);


// Token lexer
void	append_token(t_token **token_list, t_token *token);

// Lexer parser
int lexer_parse(t_token *token);
int ft_strcmp(char *s1, char *s2);

// Signals
void set_sig_action(void);
void sigint_handler(int signal);

// Parser
int parser(t_token *head, t_minishell *minishell);

// Redir parsing
void create_redir(t_cmds *cmd, t_token *head, t_minishell *minishell);

// Utils parser
const char *get_token_type_str(t_token_type type); // pour print les noms des redir
int is_redir(t_token *head_token);				   // return 1 si c est une redir

// Utils lexer
int is_separator(char c);
int is_token(char c);

// Utils 1
void *get_next_word(void *node);
void *get_next_redir(void *node);
void lst_clear(void **lst, void *(*get_next)(void *), void (*del)(void *));

// Get next token
void *get_next_token(void *node);
void *get_next_cmds(void *node);
void *get_next_word(void *node);
void *get_next_redir(void *node);

// Utils del lst
void del_cmds(void *content);
void del_redir(void *content);
void del_word(void *content);

// To delete later
void print_elements_cmds(t_word *head_w, t_redir *head_r);

#endif