#include "minishell.h"

BOOL	is_index_in_array(int index, t_array *array)
{
	int	i;

	i = 0;
	while (i < array->size)
	{
		if (index == array->arr[i])
			return (TRUE);
		else
			i++;
	}
	return (FALSE);
}

char	*sub_str(char const *s, int start, int end)
{
	char		*sub;
	size_t		i;
	size_t		len;

	if (!s)
		return (NULL);
	len = str_len(s);
	if (end >= (int)len)
		end = len;
	if (start >= end)
		return (str_dup(""));
	if (start < 0)
		start = 0;
	len = (end - start);
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	sub[len] = '\0';
	i = 0;
	while (start < end && s[start])
		sub[i++] = s[start++];
	return (sub);
}

int	skip_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c)
		i++;
	return (i);
}

char	*sub_until_chars(char *buf, int *i, char *chars)
{
	int		start;

	start = *i;
	while (buf[*i] && is_included(buf[*i], chars) == FALSE)
		(*i)++;
	return (sub_str(buf, start, *i));
}
