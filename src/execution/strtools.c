#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, int start, size_t len)
{
	int		i;
	char	*ret;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	ret = (char *)malloc(len + 1);
	while (s[start] && i < (int)len)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
