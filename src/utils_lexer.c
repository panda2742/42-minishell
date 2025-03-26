
#include "libft.h"
// renvoie  positif si c == quelque chose
int is_token(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int is_separator(char c)
{
	return (ft_isspace(c) || is_token(c));
}