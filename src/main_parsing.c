/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/13 17:28:44 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <strings.h>

char *join_tokens_to_string(t_token *tokens)
{
	char *result;
	t_token *tmp;

	result = ft_strdup("");
	tmp = tokens;
	if (!result)
		return (NULL);
	while (tmp)
	{
		if (tmp->fragments && tmp->fragments->text)
			result = str_join_free(result, tmp->fragments->text);
		if (tmp->next)
			result = str_join_free(result, " ");
		tmp = tmp->next;
	}
	return (result);
}

void	handle_is_redir_tokens(t_excmd *cmd, t_token *token)
{
		if (token->type == REDIR_IN)
			add_redirect(cmd, IN_REDIR, create_in_redirect(token->next->text));
		else if (token->type == REDIR_OUT)
			add_redirect (cmd, OUT_REDIR, create_out_redirect(token->next->text, false));
		else if (token->type == APPEND)
			add_redirect(cmd, OUT_REDIR, create_out_redirect(token->next->text, true));
		else if (token->type == HEREDOC)
			add_redirect(cmd, IN_REDIR, create_heredoc_redirect(token->next->text));
}

void	free_dom_help(t_token *token, t_token *new_tokens, t_token_list *token_list, char *line, char *final_cmd) // to delete
{
	free_tokens(token);
	free_tokens(new_tokens);
	free_tokens_in_list(token_list->tokens, token_list);
	free(line);
	free(final_cmd);
}

void	expand_caller(t_token *token, t_token **new_tokens, t_token *return_value, t_minishell *minishell)
{
	t_token	*last_new;
	t_token	*split_token;
	
	split_token = NULL;
	return_value = token;
	*new_tokens = NULL;
	last_new = NULL;
	while (return_value)
	{
		split_token = word_split_token(return_value, &minishell->env);
		if (split_token)
		{
			// Concatene la chaine de tokens obtenue via le word splitting
			if (!*new_tokens)
			{
				*new_tokens = split_token;
				last_new = *new_tokens;
			}
			else
			{
				while (last_new->next)
					last_new = last_new->next;
				last_new->next = split_token;
			}
		}
		return_value = return_value->next;
	}
}

void print_out_redir(t_redir *redir)
{
	t_redir *current = redir;
	while (current)
	{
		if (current->filepath)
			printf("redir file: %s\n", current->filepath); // redir file: chemin/vers/le/fichier
		current = current->next;
	}
}

void handle_print_cmd(t_excmd *cmd)
{

	ft_printf("cmd name: %s\n", cmd->name);
	int i = 0;
	while (cmd->argv[i])
	{
		ft_printf("cmd argv: %s\n", cmd->argv[i]);
		i++;
	}
	
	if (cmd->out_redirects.size > 0)
	{
		ft_printf("\nOutput files: \n");
		print_out_redir(cmd->out_redirects.redirects[0]);
	}
	if (cmd->in_redirects.size > 0)
	{
		ft_printf("\nInput files: \n");
		print_out_redir(cmd->in_redirects.redirects[0]);
	}


}

char *get_first_word(t_token *token)
{
	t_token *tmp = token;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			tmp->is_first_word = true;	
			return (tmp->text);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	t_token *token;
	t_token *tmp;
	// t_token *last_new;
	// t_token *split_token;
	char *final_cmd;
	t_minishell minishell;

	t_token *new_tokens;
	(void)argc;
	(void)argv;
	if (create_env(env, &minishell.env) == NULL)
	{
		ft_printf("Error initializing environment\n");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		set_sig_action();
		char *prompt = show_prompt(&minishell.env);
		line = readline(prompt);
		free(prompt);
		if (!line || !ft_strcmp(line, "exit")) // CTRL+D || "exit"
		{
			ft_printf("exit\n");
			free_env(&minishell.env);
			break;
		}
		token = ft_input(line);
		if (token == NULL)
		{
			free(line);
			continue;
		}
		if (!lexer_parse(token))
		{
			free_tokens(token);
			free(line);
			continue;
		}
		/*
		// On applique ensuite le word splitting sur chaque token.
		// Ici, word_split_token() reçoit un token et son environnement,
			et retourne une nouvelle chaine de tokens */
		print_tokens(token);

		expand_caller(token, &new_tokens, tmp, &minishell);
		final_cmd = join_tokens_to_string(new_tokens);
		ft_printf("Final command line: %s\n", final_cmd);
		
		tmp = NULL;
		t_token_list *head_list = NULL;

		token_list(new_tokens, &head_list);
		print_token_list(head_list);
		
		t_token_list *tmp_list = head_list;
		while(tmp_list)
		{
			
			if (tmp_list != NULL)
			{
				tmp = tmp_list->tokens;
				char *cmd_name = get_first_word(tmp);
				t_excmd *cmd = create_cmd(cmd_name, &minishell.env); // cmd doit etre le premier WORD rencontre, a changer
				cmd->argc = token_lstsize(tmp) - 1;
				int count_args = count_arg_words(tmp);
				cmd->raw = join_tokens_to_string(new_tokens);
				cmd->argv = malloc(sizeof(char *) *( count_args + 1));
				cmd->argv[count_args] = NULL;
				int i = 0;
				while(tmp && (tmp->type != PIPE))
				{
					if (is_redir(tmp))
					{
						handle_is_redir_tokens(cmd, tmp);					
					}
					if (tmp->type == WORD)
					{
						if (tmp->is_first_word != true)
						{
							cmd->argv[i] = tmp->text;
							i++;
						}
					}
					tmp = tmp->next;
				}

				handle_print_cmd(cmd);
			}

			tmp_list = tmp_list->next;
		}
		
		free_dom_help(token, new_tokens, head_list, line, final_cmd);

	}
	return (0);
}

// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<
