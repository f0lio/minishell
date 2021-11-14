#include "minishell.h"

void	my_strrev(char *str)
{
	int 	i;
	int 	len;
	char	tmp;

	i = -1;
	len = str_len(str);
	while (++i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
		i++;
	}
}

long	my_atoi(char *str, long res)
{
	if (*str)
		res = (*str - '0') + my_atoi(str + 1, res) * 10;
	return (res);
}

int		numlen(long num, int i)
{
	if (!(num / 10))
		return (i);
	else
		return (numlen(num / 10, ++i));
}

char	*randname(void)
{
	int		fd;
	char	*str;
	char	*ret;

	fd = open("/dev/random", O_RDONLY);
	str = malloc(sizeof(char) * 10);
	read(fd, str, 10);
	ret = str_join("/tmp/", str);
	safe_free((void **)&str);
	close(fd);
	return (ret);
}

char	*my_itoa(long num)
{
	char	*out;
	int		i;
	int		nlen;

	i = -1;
	nlen = numlen(num, 1);
	out = malloc(numlen(num, 2) * sizeof(char));
	while (++i < nlen)
	{
		out[i] = '0' + num % 10;
		num /= 10;
	}
	out[i] = 0;
	return (out);
}
void	initscmd(t_simpcmd *scmd)
{
	scmd->isbuiltin = 0;
	scmd->biexitstatus = -1;
	scmd->pid = 0;
	scmd->isappend = 0;
	scmd->heredoc = 0;
	scmd->infile = 0;
	scmd->outfile = 0;
	scmd->stdio[0] = 0;
	scmd->stdio[1] = 0;
	scmd->pipe[0] = 0;
	scmd->pipe[1] = 0;
}

char		**strcut(char *str, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	if (!len)
	// bash: export: `=test': not a valid identifier
		return (0);
	arr = malloc(sizeof(char *) * 2);
	arr[0] = malloc(sizeof(char) * (len + 1));
	arr[0][len] = 0;
	if (str[len])
	{
		// '=' sign found
		arr[1] = malloc(sizeof(char) * (str_len(str) - len));
		arr[1][str_len(str) - len - 1] = 0;
	}
	else
		arr[1] = 0;
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
	int	i;
	t_envvar	*start;

	if (!arr || !arr[0])
	{
		printf("No envp\n");
		return ;
	}
	*node = str_to_envv(arr[0]);
	start = *node;
	(*node)->prev = 0;
	(*node)->next = 0;
	i = 0;
	while (arr[++i])
	{
		(*node)->next = str_to_envv(arr[i]);
		(*node)->next->prev = *node;
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
		return 0;
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
		// printf("teslksddsm;lmds;\n");
		tmp = str_join("=", node->content);
		arr[i] = str_join(node->name, tmp);
		safe_free((void **)&tmp);
		// printf("%s\n", arr[i]);
		node = node->prev;
	}
	node = start;
	return (arr);
}

void	free_arr(char ***adr)
{
	char	**array;
	int		i;

	array = *adr;
	if (!array)
		return ;
	i = -1;
	while (array[++i])
		safe_free((void **)&array[i]);
	safe_free((void **)adr);
}

// returns duplicated string array
// element indexed with rm is skipped if rm >= 0 (and rm < array length)
// normal duplication if rm == -1
// new_elem is added if rm == -2
// most likely breaks if rm is anything else
// undefined behaviour if rm == -2 and new_elem doesnt exist
// frees arr if free
char	**arrdup(char ***arr, int rm, int free, char *new_elem)
{
	int		i;
	char	**ret;

	if (!*arr)
		return (0);
	i = 0;
	while (*arr[i])
		i++;
	ret = malloc((i + (rm == -1) + (rm == -2)) * sizeof(char *));
	i = -1;
	while (*arr[++i])
		if (rm != i)
			ret[i] = str_dup(*arr[i]);
	if (rm == -2)
		ret[i++] = str_dup(new_elem);
	ret[i] = 0;
	if (free)
		free_arr(arr);
	return (ret);
}
