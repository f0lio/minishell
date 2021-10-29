
#include "minishell.h"

char	*str_join(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	l;
	char			*s3;

	if (!s1 || !s2) //meh, better to make a dup; no need to return NULL
		return (NULL);
	i = str_len(s1) + str_len(s2);
	if (!(s3 = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	s3[i] = '\0';
	i = 0;
	while (s1[i])
	{
		s3[i] = (char)s1[i];
		i++;
	}
	l = 0;
	while (s2[l])
	{
		s3[i++] = (char)s2[l];
		l++;
	}
	return (s3);
}

/*
**	Wrapper of str_join(), it frees the old buffer after joining
*/

void str_fjoin(char **dst, char *src)
{
    char *p;

	if (dst == NULL || src == NULL)
		return ;
    p = *dst;
    *dst = str_join((const char*)*dst, (const char*)src);
    free(p);
}


t_bool	is_index_in_array(int index, t_array *array)
{
	int i;

	i = 0;
	while (i < array->size)
		if (index == array->arr[i])
			return (TRUE);
		else
			i++;
	return (FALSE);
}

char	*clean_sub_str(char const *s, int start, int end, t_array *skip_index)
{
	char		*sub;
	short		skip_num;
	size_t		i;
	size_t		len;

	if (!s)
		return (NULL);
	len = str_len(s);
	if (start > (int)len || end < 0)
		return (str_dup(""));
	start = start < 0 ? 0 : start;
	end = end >= len ? len : end;
	skip_num = 0;
	if (skip_index != NULL)
	{
		while (skip_num < skip_index->size
			&& skip_index->arr[skip_num] != -1)
			skip_num++;
	}
	if (!(sub = malloc(end - start + 1 - skip_num)))
		return (NULL);
	i = 0;
	while (start < end && s[start])
	{
		if (is_index_in_array(start, skip_index) == FALSE)
		{
			sub[i] = s[start];
			i++;
			start++;
		}
		else
			start++;
	}
	sub[start] = '\0';
	return (sub);
}

char	*sub_str(char const *s, int start, int end)
{
	char		*sub;
	size_t		i;
	size_t		len;

	if (!s)
		return (NULL);
	len = str_len(s);
	end = end >= len ? len : end;
	if (start >= end)
		return (str_dup(""));
	start = start < 0 ? 0 : start;
	
	// (start < 0) && (start = 0);
	
	len = (end - start);
	if (!(sub = malloc(len + 1)))
		return (NULL);
	sub[len] = '\0';
	i = 0;
	while (start < end && s[start])
		sub[i++] = s[start++];
	return (sub);
}

int skip_char(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] == c)
		i++;
	return 0;
}

char	*sub_until_chars(char *buf, int *i, char *chars)
{
	int		start;

	start = *i;
	while (buf[*i] && is_included(buf[*i], chars) == FALSE)
		(*i)++;
	return (sub_str(buf, start, *i));
}
