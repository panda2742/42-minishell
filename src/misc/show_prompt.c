/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:39:24 by ehosta            #+#    #+#             */
/*   Updated: 2025/05/15 14:22:47 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_get_user(t_env_manager *env);
static char	*_get_path(t_env_manager *env);
static char	*_replace_by_home(t_env_var *home_var, char *cwd);
static char	*_load_theme(t_minishell *minishell);

char	*show_prompt(t_minishell *minishell)
{
	static char	default_prompt[13] = "minishell$ ";
	char		*res;
	char		*line;

	if (!isatty(STDIN_FILENO))
		return (readline("\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"));
	res = _load_theme(minishell);
	if (res == NULL)
		return (readline(default_prompt));
	line = readline(res);
	free(res);
	return (line);
}

static char	*_get_user(t_env_manager *env)
{
	static char	default_user[7] = "shweck";
	t_env_var	*user_var;
	char		*user;

	user_var = get_var(env, "USER");
	if (!user_var || !user_var->value)
		user = (char *)default_user;
	else
		user = user_var->value;
	return (user);
}

static char	*_get_path(t_env_manager *env)
{
	static char	default_path[27] = "*its a dark place here...*";
	char		*cwd;
	t_env_var	*home_var;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup((char *)default_path));
	home_var = get_var(env, "HOME");
	if (!home_var || !home_var->value)
		return (cwd);
	return (_replace_by_home(home_var, cwd));
}

static char	*_replace_by_home(t_env_var *home_var, char *cwd)
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

static char	*_load_theme(t_minishell *minishell)
{
	const char	*user = _get_user(&minishell->env);
	const char	*path = _get_path(&minishell->env);
	char		*res;

	if (minishell->prompt_theme == -1)
	{
		minishell->prompt_theme = 0;
		if (minishell->argc >= 3)
		{
			if (ft_strcmp(minishell->argv[2], "--theme")
				&& ft_strcmp(minishell->argv[0], "-t"))
				minishell->prompt_theme = ft_atoi(minishell->argv[2]) % 4;
		}
	}
	res = NULL;
	if (minishell->prompt_theme == 3)
		res = build_theme0(user, path);
	if (minishell->prompt_theme == 1)
		res = build_theme1(minishell->last_status, user, path);
	if (minishell->prompt_theme == 2)
		res = build_theme2(minishell->last_status, path);
	if (minishell->prompt_theme == 0)
		res = NULL;
	free((char *)path);
	return (res);
}
