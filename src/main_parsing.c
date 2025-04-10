/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:24:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/10 12:01:37 by abonifac         ###   ########.fr       */
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
			add_redirect(cmd, IN_REDIR, create_in_redirect(token->next->fragments->text));
		else if (token->type == REDIR_OUT)
			add_redirect (cmd, OUT_REDIR, create_out_redirect(token->next->fragments->text, false));
		else if (token->type == APPEND)
			add_redirect(cmd, OUT_REDIR, create_out_redirect(token->next->fragments->text, true));
		else if (token->type == HEREDOC)
			add_redirect(cmd, IN_REDIR, create_heredoc_redirect(token->next->fragments->text));
}

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	t_token *token;
	t_token *tmp;
	t_token *last_new;
	t_token *split_token;
	char *final_cmd;
	t_minishell minishell;

	t_token *new_tokens; // Pour stocker le resultat du word splitting
	// Gestionnaire d'environnement (alloue et initialise via create_env)
	(void)argc;
	(void)argv;
	if (create_env(env, &minishell.env) == NULL)
	{
		ft_printf("Error initializing environment\n");
		return (EXIT_FAILURE);
	}
	char **envlst = NULL;
	t_excmd **cmds = exec_test(&minishell, &envlst);
	exec_command(&minishell, cmds);
	free_cmds(cmds);
	ft_free_strtab(envlst);
	while (1)
	{
		set_sig_action();
		char *prompt = show_prompt(&minishell.env);
		line = readline(prompt);
		free(prompt);
		if (!line || !ft_strcmp(line, "exit")) // CTRL+D || "exit"
		{
			ft_printf("exit\n");
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
		/*Ici, on a deja la phase d'expansion dans chaque token,
			et on affiche le resultat d'expansion
		// On applique ensuite le word splitting sur chaque token.
		// Ici, word_split_token() reçoit un token et son environnement,
			et retourne une nouvelle chaine de tokens */
		tmp = token;
		new_tokens = NULL;
		last_new = NULL;
		while (tmp)
		{
			split_token = word_split_token(tmp, &minishell.env);
			if (split_token)
			{
				// Concatene la chaine de tokens obtenue via le word splitting
				if (!new_tokens)
				{
					new_tokens = split_token;
					last_new = new_tokens;
				}
				else
				{
					while (last_new->next)
						last_new = last_new->next;
					last_new->next = split_token;
				}
			}
			tmp = tmp->next;
		}
		
		
		tmp = new_tokens;
		char *cmd_name = tmp->fragments->text;
		t_excmd *cmd = create_cmd(cmd_name, &minishell.env);
		cmd->argc = token_lstsize(new_tokens) - 1;
		tmp = tmp->next;
		ft_printf("cmd name: %s\n", tmp->fragments->text);
		while (tmp)
		{
			if (is_redir(tmp))
			{
				handle_is_redir_tokens(cmd, token);
			}
			if (tmp->type == WORD)
			{
				
			}
			ft_printf("test cmd: %s\n", tmp->fragments->text);
			tmp = tmp->next;
		}



		
		// On peut afficher la nouvelle liste de tokens après word splitting
		final_cmd = join_tokens_to_string(new_tokens);
		// print_tokens(token);
		ft_printf("Final command line: %s\n", final_cmd);
		print_tokens(new_tokens);
		free_tokens(token);
		free_tokens(new_tokens);
		free(line);
		free(final_cmd);
	}
	// free_env_manager(&minishell);
	return (0);
}

// cd ls -e "coucou'bon|jour'" 'bonjour"cou>cou"' | > >> < <<
