#include "minishell.h"

static int			is_split(char str, char c)
{
	if (str == c || str == '\t' || str == '\n')
		return (1);
	return (0);
}

static int			word_count(const char *str, char c)
{
	int i;
	int output;

	i = 0;
	output = 0;
	while (str[i])
	{
		if (!is_split(str[i], c) && (i == 0 || is_split(str[i - 1], c)))
		{
			output++;
			i++;
		}
			i++;
	}
	return (output);
}

static int			letter_count(const char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (!is_split(str[i], c) && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

static char			*get_word(const char *str, char a, char **arr, int k)
{
	int			i;
	char		*c;

	i = 0;
	if (!(c = malloc(letter_count(str, a) + 1)))
	{
		while (i < k)
		{
			free(*(arr + i));
			i++;
		}
		free(arr);
	}
	while (!is_split(str[i], a) && *(str + i) != '\0')
	{
		c[i] = str[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char				**ft_split(char const *str, char c)
{
	char		**array;
	int			i;
	int			k;

	i = 0;
	k = 0;
	if (!str)
		return (0);
	if (!(array = malloc(sizeof(char*) * (word_count(str, c) + 1))))
		return (0);
	while (str[i])
	{
		if (!is_split(str[i], c) && (i == 0 || is_split(str[i - 1], c)))
		{
			if (!(array[k] = get_word(&str[i], c, array, k)))
				return (0);
			k++;
		}
		i++;
	}
	array[word_count(str, c)] = 0;
	return (array);
}