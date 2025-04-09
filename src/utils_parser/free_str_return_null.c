
#include "minishell.h"

char *free_str_return_null(char *str)
{
	free(str);
	return NULL;
}
