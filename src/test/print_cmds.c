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
	printf(" [%s%p%s]\n", U_MAGENTA, cmd, RESET);
	printf("   %-12s %s%zu%s\n", "id", B_YELLOW, cmd->id, RESET);
	printf("   %-12s %s%s%s\n", "name", B_BLUE, cmd->name, RESET);
	if (cmd->in_a_child)
		printf("   %-12s %strue%s\n", "in_a_child", B_GREEN, RESET);
	else
		printf("   %-12s %sfalse%s\n", "in_a_child", B_RED, RESET);
	printf("   %-12s %s%p%s\n", "prototype", U_MAGENTA, cmd->proto, RESET);

	printf("   -\n   %-12s %s%d%s\n", "argc", B_YELLOW, cmd->argc, RESET);
	int argv_len = 0;
	while (cmd->argv[argv_len] && argv_len < 1000)
		argv_len++;
	printf("   %-12s %s%p%s (%s%d%s detected)\n", "argv", B_YELLOW, cmd->argv, RESET, B_YELLOW, argv_len, RESET);
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
	int envp_len = 0;
	while (cmd->envp[envp_len] && envp_len < 1000)
		envp_len++;
	printf("   %-12s %s%p%s (%s%d%s detected)\n", "envp", U_MAGENTA, cmd->envp, RESET, B_YELLOW, envp_len, RESET);	

	printf("   -\n   %-12s %s%s%s\n", "raw", B_BLUE, cmd->raw, RESET);

	int paths_len = 0;
	while (cmd->paths[paths_len] && paths_len < 1000)
		paths_len++;
	printf("   %-12s %s%p%s (%s%d%s detected)\n", "paths", U_MAGENTA, cmd->envp, RESET, B_YELLOW, paths_len, RESET);	

	printf("   -\n   %sinput redirections:%s\n", B_WHITE, RESET);
	printf("     %-12s %s%zu%s\n", "size", B_YELLOW, cmd->in_redirects.size, RESET);
	if (cmd->in_redirects.has_heredoc)
		printf("     %-12s %strue%s\n", "has_heredoc", B_GREEN, RESET);
	else
		printf("     %-12s %sfalse%s\n", "has_heredoc", B_RED, RESET);
	printf("     %-12s %s%d%s\n", "final_fd", B_YELLOW, cmd->in_redirects.final_fd, RESET);
	if (cmd->in_redirects.size)
	{
		printf("     list:\n");
		t_redir *redir = *cmd->in_redirects.redirects;
		while (redir)
		{
			printf("     (%s%p%s)", U_MAGENTA, redir, RESET);
			if (redir->is_heredoc)
				printf(" '<< %s%s%s'", B_BLUE, redir->heredoc_del, RESET);
			else
				printf(" '< %s%s%s'", B_BLUE, redir->filepath, RESET);
			redir = redir->next;
		}
	}
}
