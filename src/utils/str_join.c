#include "minishell.h"

char	*str_join(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	l;
	char			*s3;

	if (!s1 || !s2)
		return (NULL);
	i = str_len(s1) + str_len(s2);
	s3 = (char *)malloc((i + 1) * sizeof(char));
	if (!s3)
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
void	str_fjoin(char **dst, char *src)
{
	char	*p;

	if (dst == NULL || src == NULL)
		return ;
	p = *dst;
	*dst = str_join((const char *)*dst, (const char *)src);
	free(p);
}
