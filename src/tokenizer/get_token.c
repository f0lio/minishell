#include "minishell.h"

t_token	*make_token(t_env *env, int j, BOOL quote)
{
	t_token	*token;

	token = new_token(sub_str(env->input.line, env->input.i, j));
	if (token == NULL)
		return (NULL);
	token->quoted = (quote != 0);
	env->input.i = j;
	return (token);
}

BOOL	handle_quotes(char *line, BOOL *quote, int j, BOOL *flag)
{
	if (line[j] == *quote)
	{
		if (*flag && (!line[j + 1] || is_included(line[j + 1], "> <|")) && ++j)
			return (1);
		*quote = 0;
	}
	else if (quote == 0)
	{
		*flag = (!j || line[j - 1] == ' ');
		*quote = line[j];
	}
	return (0);
}

char	*init_vars(t_env *env, BOOL *quote, BOOL *flag, int *j)
{
	*quote = 0;
	*j = env->input.i + skip_char(&env->input.line[env->input.i], SPACE) - 1;
	*flag = FALSE;
	return (env->input.line);
}

t_token	*get_token(t_env *env, char *line)
{
	int		j;
	char	quote;
	BOOL	flag;

	line = init_vars(env, &quote, &flag, &j);
	while (++j < (int)env->input.len)
	{
		if (quote == 0 && is_included(line[j], "|") && ++j)
			break ;
		else if (quote == 0 && is_included(line[j], "><") && ++j)
		{
			j += (j != 0 && line[j] == line[j - 1]);
			break ;
		}
		else if (line[j] == SINGLE_QT || line[j] == DOUBLE_QT)
		{
			if (handle_quotes(line, &quote, j, &flag))
				break ;
		}
		else if (!quote && line[j] == ' ')
			break ;
		else if (!quote && is_included(line[j + 1], "|><") && ++j)
			break ;
	}
	return (make_token(env, j, quote));
}
