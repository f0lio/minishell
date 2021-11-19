
# include "minishell.h"

char *parse_pid()
{
	return (int_to_str(getpid()));
}

char	*parse_variable_name(char *buf, int *i)
{
	int		start;
	size_t	j;

	if (buf[*i + 1] == DOLLAR)
	{
		*i += 1;
		return (str_dup("$"));
	}
	else if (buf[*i + 1] == '?')
	{
		*i += 2;
		return (str_dup("?"));
	}
	j = *i + 1;
	start = j;
	while (is_alphanum(buf[j]) || buf[j] == '_')
		j++;
	*i = j;
	return (sub_str(buf, start, j));
}

char	*expand_dquoted_token(ENV, char *tok)
{
	char	*new_tok;
	char	*val;
	int		i;
	int		len;

	i = 0;
	val = NULL;
	new_tok = str_dup("");
	len = str_len(tok);
	while (i < len)
	{
		if (tok[i] == DOLLAR)
			val = handle_dollar_sign(env, tok, &i);
		else
		{
			val = sub_until_chars(tok, &i, "$");
			i -= (tok[i] == DOLLAR);
		}
		if (val)
		{
			str_fjoin(&new_tok, val);
			safe_free((void **)&val);
		}
		i++;
	}
	return (new_tok);
}

char *handle_dollar_sign(t_env *env, char *tok, int *i)
{
	char *val;
	char *var;

	val = NULL;
	var = NULL;
	if (tok[*i + 1] == DOLLAR
		|| (is_alphanum(tok[*i + 1]) == 0
		&& tok[*i + 1] != '_' && tok[*i + 1] != '?'))
	{
		val = str_dup("$");
		(*i)++;
	}
	else
	{
		var = parse_variable_name(tok, i);
		*i -= (tok[*i] != 0);
		if (var)
		{
			val = get_env(env, var);
			safe_free((void **)&var);
		}
	}
	return (val);
}
