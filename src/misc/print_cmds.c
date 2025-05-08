/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:23:02 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/06 12:25:26 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_excmd *cmd)
{
	static int	i = 0;

	printf("[%sCommands debugging %d%s]\n", B_BLUE, i++, RESET);
	while (cmd)
	{
		printf(" |\n");
		print_cmd(cmd);
		cmd = cmd->next;
	}
	printf("\n");
}

void	print_cmd(t_excmd *cmd)
{
	int		argv_len;
	int		envp_len;
	int		paths_len;
	t_redir	*redir;

	printf("[%p] [%s%p%s]\n", cmd, U_MAGENTA, cmd, RESET);
	if (cmd == NULL)
		return ;
	printf("[%p]   %-12s %s%zu%s\n", cmd, "id", B_YELLOW, cmd->id, RESET);
	printf("[%p]   %-12s %s%s%s\n", cmd, "name", B_BLUE, cmd->name, RESET);
	if (cmd->in_a_child)
		printf("[%p]   %-12s %strue%s\n", cmd, "in_a_child", B_GREEN, RESET);
	else
		printf("[%p]   %-12s %sfalse%s\n", cmd, "in_a_child", B_RED, RESET);
	printf("[%p]   %-12s %s%p%s\n", cmd, "prototype", U_MAGENTA, cmd->proto, RESET);
	printf("[%p]   -\n[%p]   %-12s %s%d%s\n", cmd, cmd, "argc", B_YELLOW, cmd->argc, RESET);
	argv_len = 0;
	while (cmd->argv[argv_len] && argv_len < 1000)
		argv_len++;
	printf("[%p]   %-12s %s%p%s (%s%d%s detected)\n", cmd, "argv", B_YELLOW, cmd->argv, RESET, B_YELLOW, argv_len, RESET);
	if (argv_len)
	{
		printf("[%p]    %-11s [", cmd, "values: ");
		argv_len = 0;
		while (cmd->argv[argv_len])
		{
			printf("%s%s%s", B_BLUE, cmd->argv[argv_len], RESET);
			if (cmd->argv[argv_len + 1])
				printf(", ");
			argv_len++;
		}
		printf("]\n[%p]   -\n", cmd);
	}
	printf("[%p]   %-12s %s%p%s\n", cmd, "env", U_MAGENTA, cmd->env, RESET);
	envp_len = 0;
	while (cmd->envp[envp_len] && envp_len < 1000)
		envp_len++;
	printf("[%p]   %-12s %s%p%s (%s%d%s detected)\n", cmd, "envp", U_MAGENTA, cmd->envp, RESET, B_YELLOW, envp_len, RESET);
	paths_len = 0;
	while (cmd->paths[paths_len] && paths_len < 1000)
		paths_len++;
	printf("[%p]   -\n[%p]   %-12s %s%p%s (%s%d%s detected)\n", cmd, cmd, "paths", U_MAGENTA, cmd->envp, RESET, B_YELLOW, paths_len, RESET);
	printf("[%p]   -\n[%p]   %sinput redirections:%s\n", cmd, cmd, B_WHITE, RESET);
	printf("[%p]     %-12s %s%zu%s\n", cmd, "size", B_YELLOW, cmd->in_redirects.size, RESET);
	if (cmd->in_redirects.has_heredoc)
		printf("[%p]     %-12s %strue%s\n", cmd, "has_heredoc", B_GREEN, RESET);
	else
		printf("[%p]     %-12s %sfalse%s\n", cmd, "has_heredoc", B_RED, RESET);
	printf("[%p]     %-12s %s%d%s\n", cmd, "final_fd", B_YELLOW, cmd->in_redirects.final_fd.fd, RESET);
	if (cmd->in_redirects.size)
	{
		printf("[%p]     list:\n", cmd);
		redir = *cmd->in_redirects.redirects;
		while (redir)
		{
			printf("[%p]     (%s%p%s)", cmd, U_MAGENTA, redir, RESET);
			if (redir->is_heredoc)
				printf(" \"%s<< %s%s\"", B_BLUE, redir->heredoc_del, RESET);
			else
				printf(" \"%s< %s%s\"", B_BLUE, redir->filepath, RESET);
			printf(" | fd %s%d%s", B_YELLOW, redir->fd.fd, RESET);
			if (redir->fd.fd == -2)
				printf(" %sTOKEN_HEREDOC%s", B_RED, RESET);
			else if (redir->fd.fd == -1)
				printf(" %sCLOSED%s", B_RED, RESET);
			else if (redir->fd.fd == 0)
				printf(" %sSTDIN (default)%s", B_BLUE, RESET);
			else if (redir->fd.fd == 1)
				printf(" %sSTDOUT (default)%s", B_BLUE, RESET);
			else
				printf(" %sOPEN%s", B_GREEN, RESET);
			printf(" -> (%s%p%s)\n", U_MAGENTA, redir->next, RESET);
			printf("[%p]     here_doc content:\n%s%s%s\n", cmd, BLACK, redir->heredoc_content, RESET);
			redir = redir->next;
		}
	}
	printf("[%p]   -\n[%p]   %soutput redirections:%s\n", cmd, cmd, B_WHITE, RESET);
	printf("[%p]     %-12s %s%zu%s\n", cmd, "size", B_YELLOW, cmd->out_redirects.size, RESET);
	if (cmd->out_redirects.has_heredoc)
		printf("[%p]     %-12s %strue%s\n", cmd, "has_heredoc", B_GREEN, RESET);
	else
		printf("[%p]     %-12s %sfalse%s\n", cmd, "has_heredoc", B_RED, RESET);
	printf("[%p]     %-12s %s%d%s\n", cmd, "final_fd", B_YELLOW,
		cmd->out_redirects.final_fd.fd, RESET);
	if (cmd->out_redirects.size)
	{
		printf("[%p]     list:\n", cmd);
		redir = *cmd->out_redirects.redirects;
		while (redir)
		{
			printf("[%p]     (%s%p%s)", cmd, U_MAGENTA, redir, RESET);
			if (redir->out_append_mode)
				printf(" \"%s>> %s%s\"", B_BLUE, redir->filepath, RESET);
			else
				printf(" \"%s> %s%s\"", B_BLUE, redir->filepath, RESET);
			printf(" | fd %s%d%s", B_YELLOW, redir->fd.fd, RESET);
			if (redir->fd.fd == -2)
				printf(" %sTOKEN_HEREDOC%s", B_RED, RESET);
			else if (redir->fd.fd == -1)
				printf(" %sCLOSED%s", B_RED, RESET);
			else if (redir->fd.fd == 0)
				printf(" %sSTDIN (default)%s", B_BLUE, RESET);
			else if (redir->fd.fd == 1)
				printf(" %sSTDOUT (default)%s", B_BLUE, RESET);
			else
				printf(" %sOPEN%s", B_GREEN, RESET);
			printf(" -> (%s%p%s)\n", U_MAGENTA, redir->next, RESET);
			redir = redir->next;
		}
	}
	printf("[%p]   -\n[%p]   %-12s ", cmd, cmd, "pipe");
	if (cmd->pipe_open[0])
		printf("[%sOPEN%s, ", B_GREEN, RESET);
	else
		printf("[%sCLOSED%s, ", B_RED, RESET);
	if (cmd->pipe_open[1])
		printf("%sOPEN%s]", B_GREEN, RESET);
	else
		printf("%sCLOSED%s]", B_RED, RESET);
	printf("[%s%d%s, %s%d%s]\n", B_YELLOW, cmd->pipe[0], RESET, B_YELLOW, cmd->pipe[1], RESET);
	printf("[%p]   -\n[%p]   %s%p%s <= %s%p%s => %s%p%s\n", cmd, cmd, WHITE, cmd->prev, RESET, U_MAGENTA, cmd, RESET, WHITE, cmd->next, RESET);
}
