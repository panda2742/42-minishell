/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:23:02 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/14 15:25:53 by ehosta           ###   ########.fr       */
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

	printf(" [%s%p%s]\n", U_MAGENTA, cmd, RESET);
	printf("   %-12s %s%zu%s\n", "id", B_YELLOW, cmd->id, RESET);
	printf("   %-12s %s%s%s\n", "name", B_BLUE, cmd->name, RESET);
	if (cmd->in_a_child)
		printf("   %-12s %strue%s\n", "in_a_child", B_GREEN, RESET);
	else
		printf("   %-12s %sfalse%s\n", "in_a_child", B_RED, RESET);
	printf("   %-12s %s%p%s\n", "prototype", U_MAGENTA, cmd->proto, RESET);
	printf("   -\n   %-12s %s%d%s\n", "argc", B_YELLOW, cmd->argc, RESET);
	argv_len = 0;
	while (cmd->argv[argv_len] && argv_len < 1000)
		argv_len++;
	printf("   %-12s %s%p%s (%s%d%s detected)\n", "argv", B_YELLOW, cmd->argv,
		RESET, B_YELLOW, argv_len, RESET);
	if (argv_len)
	{
		printf("    %-11s [", "values: ");
		argv_len = 0;
		while (cmd->argv[argv_len])
		{
			printf("%s%s%s", B_BLUE, cmd->argv[argv_len], RESET);
			if (cmd->argv[argv_len + 1])
				printf(", ");
			argv_len++;
		}
		printf("]\n   -\n");
	}
	printf("   %-12s %s%p%s\n", "env", U_MAGENTA, cmd->env, RESET);
	envp_len = 0;
	while (cmd->envp[envp_len] && envp_len < 1000)
		envp_len++;
	printf("   %-12s %s%p%s (%s%d%s detected)\n", "envp", U_MAGENTA, cmd->envp,
		RESET, B_YELLOW, envp_len, RESET);
	printf("   -\n   %-12s %s%s%s\n", "raw", B_BLUE, cmd->raw, RESET);
	paths_len = 0;
	while (cmd->paths[paths_len] && paths_len < 1000)
		paths_len++;
	printf("   %-12s %s%p%s (%s%d%s detected)\n", "paths", U_MAGENTA, cmd->envp,
		RESET, B_YELLOW, paths_len, RESET);
	printf("   -\n   %sinput redirections:%s\n", B_WHITE, RESET);
	printf("     %-12s %s%zu%s\n", "size", B_YELLOW, cmd->in_redirects.size,
		RESET);
	if (cmd->in_redirects.has_heredoc)
		printf("     %-12s %strue%s\n", "has_heredoc", B_GREEN, RESET);
	else
		printf("     %-12s %sfalse%s\n", "has_heredoc", B_RED, RESET);
	printf("     %-12s %s%d%s\n", "final_fd", B_YELLOW,
		cmd->in_redirects.final_fd, RESET);
	if (cmd->in_redirects.size)
	{
		printf("     list:\n");
		redir = *cmd->in_redirects.redirects;
		while (redir)
		{
			printf("     (%s%p%s)", U_MAGENTA, redir, RESET);
			if (redir->is_heredoc)
				printf(" \"%s<< %s%s\"", B_BLUE, redir->heredoc_del, RESET);
			else
				printf(" \"%s< %s%s\"", B_BLUE, redir->filepath, RESET);
			printf(" | fd %s%d%s", B_YELLOW, redir->fd, RESET);
			if (redir->fd == -2)
				printf(" %sHEREDOC%s", B_RED, RESET);
			else if (redir->fd == -1)
				printf(" %sCLOSED%s", B_RED, RESET);
			else if (redir->fd == 0)
				printf(" %sSTDIN (default)%s", B_BLUE, RESET);
			else if (redir->fd == 1)
				printf(" %sSTDOUT (default)%s", B_BLUE, RESET);
			else
				printf(" %sOPEN%s", B_GREEN, RESET);
			printf(" -> (%s%p%s)\n", U_MAGENTA, redir->next, RESET);
			printf("     here_doc content:\n%s%s%s\n", BLACK,
				redir->heredoc_content, RESET);
			redir = redir->next;
		}
	}
	printf("   -\n   %soutput redirections:%s\n", B_WHITE, RESET);
	printf("     %-12s %s%zu%s\n", "size", B_YELLOW, cmd->out_redirects.size,
		RESET);
	if (cmd->out_redirects.has_heredoc)
		printf("     %-12s %strue%s\n", "has_heredoc", B_GREEN, RESET);
	else
		printf("     %-12s %sfalse%s\n", "has_heredoc", B_RED, RESET);
	printf("     %-12s %s%d%s\n", "final_fd", B_YELLOW,
		cmd->out_redirects.final_fd, RESET);
	if (cmd->out_redirects.size)
	{
		printf("     list:\n");
		redir = *cmd->out_redirects.redirects;
		while (redir)
		{
			printf("     (%s%p%s)", U_MAGENTA, redir, RESET);
			if (redir->out_append_mode)
				printf(" \"%s>> %s%s\"", B_BLUE, redir->filepath, RESET);
			else
				printf(" \"%s> %s%s\"", B_BLUE, redir->filepath, RESET);
			printf(" | fd %s%d%s", B_YELLOW, redir->fd, RESET);
			if (redir->fd == -2)
				printf(" %sHEREDOC%s", B_RED, RESET);
			else if (redir->fd == -1)
				printf(" %sCLOSED%s", B_RED, RESET);
			else if (redir->fd == 0)
				printf(" %sSTDIN (default)%s", B_BLUE, RESET);
			else if (redir->fd == 1)
				printf(" %sSTDOUT (default)%s", B_BLUE, RESET);
			else
				printf(" %sOPEN%s", B_GREEN, RESET);
			printf(" -> (%s%p%s)\n", U_MAGENTA, redir->next, RESET);
			redir = redir->next;
		}
	}
	printf("   -\n   %-12s ", "pipe");
	if (cmd->pipe_open)
		printf("%sOPEN%s [%s%d%s, %s%d%s]\n", B_GREEN, RESET, B_YELLOW,
			cmd->pipe[0], RESET, B_YELLOW, cmd->pipe[1], RESET);
	else
		printf("%sCLOSED%s [%s0%s, %s0%s]\n", B_RED, RESET, B_YELLOW, RESET,
			B_YELLOW, RESET);
	printf("   %-12s %s%d%s\n", "status", B_YELLOW, cmd->status, RESET);
	printf("   -\n   %s%p%s <= %s%p%s => %s%p%s\n", WHITE, cmd->prev, RESET,
		U_MAGENTA, cmd, RESET, WHITE, cmd->next, RESET);
}
