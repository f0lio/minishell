
#include "minishell.h"

BOOL	find_eol(char *buff)
{
	if (!buff)
		return (FALSE);
	while (*buff)
		if (*buff != EOL)
			return (TRUE);
		else
			(*buff)++;
	return (FALSE);
}

size_t	line_len(const char *line)
{
	//return ((size_t)char_addr(EOL, line) - line);
	return 0;
}

BOOL	line_is_empty(char *line)
{
	// if (line[0] == EOL && line[1] == 0)
	if (line[0] == 0)
		return (TRUE);
	return (FALSE);
}

BOOL	line_is_whitespaces(char *line)
{
	unsigned i;

	if (line_is_empty(line))
		return TRUE;
	i = 0;
	while (line[i])
	{
		if (!is_included(line[i], WHITESPACES))
			return FALSE;
		i++;
	}
	return (TRUE);
}



char	*str_dup(const char *str)
{
	size_t			i;
	size_t			len;
	char			*dup;

	if (str == NULL)
		len = 0;
	else
		len = str_len(str);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	dup[len] = 0;
	i = -1;
	while (++i < len)
		dup[i] = str[i];
	return (dup);
}

char	**str_dup_2d(char **src)
{
	char	**dup;
	int		len;
	int		i;

	if (src == NULL)
		return NULL;
	len = 0;
	while (src[len])
		len++;
	if (len == 0)
		return NULL;
	dup = (char**)malloc(len + 1);
	if (!dup)
		return NULL;
	dup[len] = NULL;
	while (--len > -1)
		dup[len] = str_dup(src[len]);
	return dup;
}

