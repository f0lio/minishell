#include "minishell.h"

BOOL	handle_sinqle_quote(char *input, char **new_input, int *i)
{
	BOOL	ret;
	char	*va;

	ret = TRUE;
	*i += (input[*i] == SINGLE_QT);
	va = sub_until_chars(input, i, "'");
	str_fjoin(new_input, "'");
	str_fjoin(new_input, va);
	str_fjoin(new_input, "'");
	if (input[*i] == SINGLE_QT)
		ret = FALSE;
	*i += (input[*i] == SINGLE_QT);
	safe_free((void **)&va);
	return (ret);
}

BOOL	handle_double_quote(
	t_env *env, char *input, char **new_input, int *i)
{
	char	*va;
	char	*p;
	BOOL	ret;

	*i += (input[*i] == DOUBLE_QT);
	va = sub_until_chars(input, i, "\"");
	ret = (input[*i] == DOUBLE_QT);
	*i += ret;
	if (va)
	{
		p = va;
		va = expand_dquoted_token(env, va);
		str_fjoin(new_input, "\"");
		str_fjoin(new_input, va);
		str_fjoin(new_input, "\"");
		safe_free((void **)&p);
		safe_free((void **)&va);
	}
	return (!ret);
}

void	handle_unquoted_dollar(
	t_env *env, char *input, char **new_input, int *i)
{
	char	*va;
	char	*p;

	if (input[*i + 1] == DOLLAR || (is_alphanum(input[*i + 1]) == 0
			&& input[*i + 1] != '_' && input[*i + 1] != '?'))
	{
		str_fjoin(new_input, "$");
		return ;
	}
	va = parse_variable_name(input, i);
	p = va;
	va = get_env(env, va);
	safe_free((void **)&p);
	*i -= (va != NULL);
	if (va)
		str_fjoin(new_input, va);
}

void	handle_unquoted_token(char *input, char **new_input, int *i)
{
	char	*va;

	va = sub_until_chars(input, i, "$\"'");
	if (va)
	{
		str_fjoin(new_input, va);
		safe_free((void **)&va);
	}	
}
