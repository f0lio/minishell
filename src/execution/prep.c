#include "minishell.h"

char	**token_to_arr(t_token *tokens, int tokcout)
{
	int		i;
	char	**arr;

	i = 0;
	arr = malloc(sizeof(char *) * (tokcout + 1));
	while (i < tokcout)
	{
		arr[i] = tokens[i].tok;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

char	*search_cmd(char *cmd, char **paths)
{
	char		*str;
	int			i;
	struct stat	buf;
	int			ret;

	i = -1;
	ret = 1;
	str = malloc(sizeof(char) * 2);
	str[0] = '/';
	str[1] = 0;
	cmd = str_join(str, cmd);
	while (ret && paths && paths[++i])
	{
		safe_free((void **)&str);
		str = str_join(paths[i], cmd);
		ret = stat(str, &buf);
	}
	safe_free((void **)&cmd);
	if (!paths || !paths[i])
	{
		safe_free((void **)&str);
		return (NULL);
	}
	return (str);
}

int	search_path(char *path)
{
	int			i;
	int			j;
	int			ret;
	struct stat	buf;

	i = -1;
	j = -1;
	while (path[++i])
		if (path[i] == '/')
			j = i;
	if (j < 0)
		return (1);
	ret = stat(path, &buf);
	if (!ret && !(buf.st_mode & S_IXUSR))
		errno = EACCES;
	if (!ret && buf.st_mode & S_IFDIR)
		errno = EISDIR;
	if (ret || !(buf.st_mode & S_IXUSR) || (buf.st_mode & S_IFDIR))
	{
		print_err(path, strerror(errno), 0, 0);
		return (127);
	}
	return (0);
}
