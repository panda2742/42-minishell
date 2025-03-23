/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:32:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/03/23 16:19:02 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef enum e_token_type {
	WORD, PIPE, REDIR_IN, REDIR_OUT, APPEND, HEREDOC
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *value;
	int expand;
	int	index;
	struct s_token *next;
} t_token;

// $VAR
# define NO_EXPAND 0 
# define EXPAND 1


// Lexer
t_token	*ft_input(char *string);
void	ft_print_tokens(t_token *head);
t_token	*ft_create_token(t_token_type type, char *value, int expand, t_token **head);
void	token_clear(t_token **lst, void (*del)(void *));
void	del_token(void *content);

// Signals
void	set_sig_action(void);
void	sigint_handler(int signal);

// Parser
int parser(t_token *head);




#endif