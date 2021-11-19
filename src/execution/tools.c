#include "minishell.h"

long	my_atoi(char *str)
{
	long	topple;
	int		i;
	int		cond;

	topple = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	cond = (str[i] == '-');
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		topple = str[i++] - '0' + topple * 10;
		if (topple > __LONG_MAX__ || topple < 0)
		{
			print_err(SHELL_NAME, "exit", str, ERR_NUM_WRONG);
			return (255);
		}
	}
	return ((long)topple * (cond * -2 + 1));
}

char	**strcut(char *str, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	arr = malloc(sizeof(char *) * 2);
	arr[0] = malloc(sizeof(char) * (len + 1));
	arr[0][len] = 0;
	if (str[len])
		arr[1] = malloc(sizeof(char) * (str_len(str) - len));
	else
		arr[1] = NULL;
	j = -1;
	i = 0;
	while (str[++j])
	{
		if (!i && (str[j] == c))
			i++;
		arr[i][j - len * i] = str[j + i];
	}
	return (arr);
}

t_envvar	*str_to_envv(char *str)
{
	t_envvar	*ev;
	char		**tmp;

	ev = malloc(sizeof(t_envvar));
	tmp = strcut(str, '=');
	ev->name = tmp[0];
	ev->content = tmp[1];
	safe_free((void **)&tmp);
	return (ev);
}

void	arr_to_ll(char **arr, t_envvar **node)
{
	int			i;
	t_envvar	*start;

	*node = str_to_envv("?=0");
	start = *node;
	(*node)->prev = 0;
	(*node)->next = 0;
	if (!arr || !arr[0])
		return ;
	i = -1;
	while (arr[++i])
	{
		(*node)->next = str_to_envv(arr[i]);
		(*node)->next->prev = *node;
		(*node)->next->next = 0;
		*node = (*node)->next;
	}
	*node = start;
}

char	**ll_to_arr(t_envvar *node)
{
	int			i;
	char		**arr;
	char		*tmp;
	t_envvar	*start;

	if (!node)
		return (0);
	while (node->prev)
		node = node->prev;
	start = node;
	i = 1;
	while (node->next && ++i)
		node = node->next;
	arr = malloc(sizeof(char *) * (i + 1));
	arr[i] = NULL;
	while (i--)
	{
		tmp = str_join("=", node->content);
		arr[i] = str_join(node->name, tmp);
		safe_free((void **)&tmp);
		node = node->prev;
	}
	node = start;
	return (arr);
}
