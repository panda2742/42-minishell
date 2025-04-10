#include "minishell.h"

void	*empty_tab(void)
{
	static void	*tab[1] = {NULL};

	return (tab);
}
