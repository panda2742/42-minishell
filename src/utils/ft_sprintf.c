#include "minishell.h"

static size_t	_total_len(const char *format, va_list args);
static char		*_write_res(const char *format, va_list args, char *buffer);

char	*ft_sprintf(const char *format, ...)
{
	va_list	args;
	char	*res;
	size_t	len;

	if (!format || !*format)
		return (NULL);
	va_start(args, format);
	len = _total_len(format, args);
	va_end(args);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = 0;
	va_start(args, format);
	res = _write_res(format, args, res);
	va_end(args);
	return (res);
}

static size_t	_total_len(const char *format, va_list args)
{
	size_t	len;

	len = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) == 's')
		{
			len += ft_strlen(va_arg(args, char *));
			format++;
		}
		else
			len++;
		format++;
	}
	return (len);
}

static char	*_write_res(const char *format, va_list args, char *buffer)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	i = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) == 's')
		{
			str = va_arg(args, char *);
			len = ft_strlen(str);
			j = -1;
			while (++j < len)
			{
				buffer[i] = str[j];
				i++;
			}
			format++;
		}
		else
		{
			buffer[i] = *format;
			i++;
		}
		format++;
	}
	return (buffer);
}
