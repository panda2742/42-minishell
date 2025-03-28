#include "minishell.h"

static char	*_get_user(t_env_manager *env);
static char	*_get_path(t_env_manager *env);
static char	*_replace_by_home(t_env *home_var, char *cwd);

char	*show_prompt(t_env_manager *env)
{
	const char	*user = _get_user(env);
	const char	*path = _get_path(env);
	char		*res;

	res = ft_sprintf(
			"%sMinishell%s::%s%s%s @ %s%s%s %s>%s ",
			B_MAGENTA, RESET,
			B_BLUE, user, RESET,
			B_CYAN, path, RESET,
			B_MAGENTA, RESET
			);
	free((char *)path);
	return (res);
}

static char	*_get_user(t_env_manager *env)
{
	static char	default_user[8] = "unknown";
	t_env		*user_var;
	char		*user;

	user_var = get_var(env, "USER");
	if (!user_var || !user_var->value)
		user = ft_strdup((char *)default_user);
	else
		user = user_var->value;
	return (user);
}

static char	*_get_path(t_env_manager *env)
{
	static char	default_path[6] = "?/?";
	char		*cwd;
	t_env		*home_var;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup((char *)default_path));
	home_var = get_var(env, "HOME");
	if (!home_var || !home_var->value)
		return (cwd);
	return (_replace_by_home(home_var, cwd));
}

static char	*_replace_by_home(t_env *home_var, char *cwd)
{
	const size_t	home_len = ft_strlen(home_var->value);
	size_t			i;
	size_t			len;

	i = -1;
	while (++i < home_len && cwd[i])
	{
		if (cwd[i] != home_var->value[i])
			return (cwd);
	}
	len = ft_strlen(cwd + i);
	ft_memmove(cwd + 1, cwd + i, len);
	cwd[0] = '~';
	cwd[len + 1] = 0;
	return (cwd);
}
