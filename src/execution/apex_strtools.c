#include "minishell.h"

int	c_w(char *str, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
			j++;
		while (str[i] != c && str[i])
			i++;
	}
	return (j);
}

char	**freemem(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

int	s_p(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	return (i);
}

int	len_str(char *s, int i, char c)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char *s, char c)
{
	char	**cpy;
	int		k;
	int		i;
	int		start;

	k = -1;
	i = 0;
	if (!s)
		return (0);
	cpy = malloc(sizeof(char *) * (c_w(s, c) + 1));
	while (s[i])
	{
		i += s_p(&s[i], c);
		start = i;
		if (len_str(s, i, c))
		{
			cpy[++k] = ft_substr(s, start, len_str(s, i, c));
			if (!(cpy[k]))
				return (freemem(cpy));
		}
		i += len_str(s, i, c);
	}
	cpy[++k] = 0;
	return (cpy);
}
