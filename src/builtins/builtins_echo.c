#include "minishell.h"

t_exit	builtins_echo(t_command *c)
{
	const size_t	len = ft_strlen(c->arg_str);
	const char		*s = c->arg_str;
	size_t			i;
	t_bool			continue_nl;
	char			current_quote;

	i = -1;
	(void)s;
	current_quote = 0;
	while (++i < len)
	{
		// if (*)
	}
	continue_nl = false;
	printf("%d\n", continue_nl);
	return (0);
}
