#include "minishell.h"

char	**error_msgs(void)
{
	static char *error_msgs[1] = {
		"cd: requires only one argument."
	};

	return (error_msgs);
}
