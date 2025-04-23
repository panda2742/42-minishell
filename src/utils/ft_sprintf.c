/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:29:51 by ehosta            #+#    #+#             */
/*   Updated: 2025/04/16 11:24:15 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	_total_len(const char *format, va_list args);
static char		*_write_res(const char *format, va_list args, char *buffer);
static char		*_handle_string(va_list args, size_t *i, char *buffer);
static size_t	_int_size(int n);
static char		*_handle_int(va_list args, size_t *i, char *buffer);

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
	res = ft_memalloc(sizeof(char) * (len + 1));
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
		else if (*format == '%' && *(format + 1) == 'd')
		{
			len += _int_size(va_arg(args, int));
			format++;
		}
		else
			len++;
		format++;
	}
	return (len);
}

static size_t	_int_size(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*_write_res(const char *format, va_list args, char *buffer)
{
	size_t	i;

	i = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) == 's')
		{
			_handle_string(args, &i, buffer);
			format++;
		}
		else if (*format == '%' && *(format + 1) == 'd')
		{
			_handle_int(args, &i, buffer);
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

static char	*_handle_string(va_list args, size_t *i, char *buffer)
{
	char	*str;
	size_t	len;
	size_t	j;

	str = va_arg(args, char *);
	len = ft_strlen(str);
	j = -1;
	while (++j < len)
	{
		buffer[*i] = str[j];
		(*i)++;
	}
	return (buffer);
}

static char	*_handle_int(va_list args, size_t *i, char *buffer)
{
	int		nb;
	size_t	len;
	size_t	j;

	nb = va_arg(args, int);
	len = _int_size(nb);
	if (nb < 0)
	{
		buffer[*i] = '-';
		(*i)++;
		nb = -nb;
		len--;
	}
	j = -1;
	while (++j < len)
	{
		buffer[*i + len - j - 1] = (nb % 10) + '0';
		nb /= 10;
	}
	(*i) += len;
	return (buffer);
}
