
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

char    *sub_until_chars(char *buf, int *i, char *chars)
{
	int         start;

	start = *i;
	while (buf[*i] && is_included(buf[*i], chars) == FALSE)
		(*i)++;
	return (sub_str(buf, start, *i));
}

char    *expand_token(ENV, char *tok)
{
	char	*new_tok;
	char	*p;
	char	*va;
	int		i;
	int		len;

	new_tok = str_dup("");
	va = str_dup("");
	len = str_len(tok);
	i = 0;
	while (i < len)
	{
		va = sub_until_chars(tok, &i, "$");
		str_fjoin(&new_tok, va);
		
		if (i >= len)
			break ;
		
		printf ("(%c, %c)\n", tok[i], tok[i + 1]);

		if (tok[i + 1] == DOLLAR)
		{
			printf ("$$$$$$$$$$$$$ %d [%s]\n", i, &tok[i]);
			va = int_to_str(getpid());
			i += 1;
		}
		else if (tok[i] == DOLLAR)
		{
		
			p = va;
			va = getenv(va); // TODO: should get from my own envv
			safe_free((void**)&p);
		}
		if (va)
			str_fjoin(&new_tok, va);
		// safe_free((void**)&va);
		i++;
	}
	return new_tok;
}

char *parse_pid()
{
	return (int_to_str(getpid()));
}
