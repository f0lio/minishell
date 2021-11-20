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

int	is_alphatiriblwit(char c, int i)
{
	if (i && c >= '0' && c <= '9')
		return (TRUE);
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (TRUE);
	return (FALSE);
}

void	move_redir_down(t_command *command, int i, int j)
{
	char	*tmp;
	int		k;
	int		l;

	l = 2;
	while (l--)
	{
		k = -1;
		while (command->scmd[i].tokarr[j + ++k + 1])
		{
			tmp = command->scmd[i].tokarr[j + k];
			command->scmd[i].tokarr[j + k] = command->scmd[i].tokarr[j + k + 1];
			command->scmd[i].tokarr[j + k + 1] = tmp;
		}
		if (!l)
			command->scmd[i].tokarr[j + k - 1] = NULL;
	}
}

void	set_exitcode(t_env *env)
{
	if (!env->envll)
		return ;
	while (env->envll->next && !str_cmp(env->envll->name, "?"))
		env->envll = env->envll->next;
	if (str_cmp(env->envll->name, "?"))
	{
		safe_free((void **)&env->envll->content);
		env->envll->content = int_to_str(env->exitcode);
	}
	while (env->envll->prev)
		env->envll = env->envll->prev;
}
