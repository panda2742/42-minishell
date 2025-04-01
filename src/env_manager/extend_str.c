#include "minishell.h"

char	*extend_str(t_env_manager *env, const char *str, size_t bytes)
{
	char	*res;
	size_t	len;
	size_t	p;
	t_bool	dollar_mode;
	size_t	strln;

	char		c;
	char		*sample;
	size_t		sampleln;
	size_t		size;
	size_t		i;
	t_env_var	*var_content;

	p = 0;
	len = 0;
	dollar_mode = false;
	res = NULL;
	i = 0;
	var_content = NULL;
	strln = ft_strlen(str);
	while (p < strln && str[p] && --bytes >= 0)
	{
		if (!dollar_mode)
		{
			if (str[p] == '$')
			{
				i = 0;
				dollar_mode = true;
				sample = ft_strdup(&str[p + 1]);
				sampleln = ft_strlen(sample);
				continue ;
			}
			else
			{
				len++;
				printf("%c", str[p]);
			}
			p++;
		}
		else
		{
			if (i > sampleln)
			{
				dollar_mode = false;
				free(sample);
				if (var_content)
				{
					p += i;
					printf("%s", var_content->value);
					len += var_content->value_length;
					var_content = NULL;
				}
				else
				{
					printf("$");
					p++;
				}
				continue ;
			}
			c = sample[i];
			sample[i] = 0;
			nb_by_name(env, sample, &size);

			if (size)
				var_content = get_var(env, sample);
			else if (size == 0)
			{
				dollar_mode = false;
				free(sample);
				if (var_content)
				{
					p += i;
					printf("%s", var_content->value);
					len += var_content->value_length;
					var_content = NULL;
				}
				else
				{
					printf("$");
					len++;
					p++;
				}
				continue ;
			}

			sample[i] = c;
			i++;
		}
	}
	printf("\n%zu\n", len);
	return (res);
}
