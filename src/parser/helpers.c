
# include "minishell.h"

char    *parse_variable_name(char *buf, int *i)
{
	int     start;
	size_t     j;

	if (buf[*i + 1] == DOLLAR)
	{
		*i += 1;
		return (str_dup("$"));
	}
	j = *i + 1;
	start = j;
	while (is_alphanum(buf[j]) || buf[j] == '_')
		j++;
	*i = j;
	return (sub_str(buf, start, j));
}

char	*sub_until_chars(char *buf, int *i, char *chars)
{
	int		start;

	start = *i;
	while (buf[*i] && is_included(buf[*i], chars) == FALSE)
		(*i)++;
	return (sub_str(buf, start, *i));
}

char    *expand_token(ENV, char *tok)
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
			val = handle_dollar_sign(tok, &i);
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
	return new_tok;
}

char *parse_pid()
{
	return (int_to_str(getpid()));
}

char *handle_dollar_sign(char *tok, int *i)
{
	char *val;
	char *var;

	val = NULL;
	var = NULL;
	if (tok[*i + 1] == DOLLAR)
	{
		val = int_to_str(getpid());
		(*i)++;
	}
	else if (!is_alphanum(tok[*i + 1]) && tok[*i + 1] != '_')
		val = strdup("$");	
	else
	{
		var = parse_variable_name(tok, i);
		*i -= (tok[*i] != 0);
		if (var)
		{
			val = str_dup(getenv(var)); //does not allocate? so i shud str_dup it?
			safe_free((void **)&var);
		}
	}
	return val;
}