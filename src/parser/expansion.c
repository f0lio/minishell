#include "minishell.h"

// Warning! This a black box! Don't try to read it. 

void expand_input(t_env *env)
{
	char	*va;
	char	*p;
	char	*new_input;
	char	*input;
	char	*buf;
	int		i;

	BOOL	dq = 0;
	BOOL	sq = 0;

	input = env->input->line;
	new_input = str_dup("");
	i = 0;
	while (i < env->input->len)
	{
		sq += (i == 0 || input[i - 1] != BACK_SLASH) * (input[i] == SINGLE_QT);
		dq += (i == 0 || input[i - 1] != BACK_SLASH) * (input[i] == DOUBLE_QT);
		if (sq)
		{
			i += (input[i] == SINGLE_QT);
			va = sub_until_chars(input, &i, "'");
			str_fjoin(&new_input, va);
			if (input[i] == SINGLE_QT)
				sq = FALSE;
			i += (input[i] == SINGLE_QT);
		}
		else if (dq)
		{
			i += (input[i] == DOUBLE_QT);
			p = va;
			va = sub_until_chars(input, &i, "\"");
			i += (input[i] == DOUBLE_QT);
			va = expand_token(env, va);	
			str_fjoin(&new_input, va);
			dq = FALSE;
		}
		if (input[i] == DOLLAR && (i == 0 || input[i - 1] != BACK_SLASH))
		{
			if (input[i + 1] == DOLLAR)
			{
				str_fjoin(&new_input, int_to_str(getpid()));
				i++;
			}
			else
			{
			va = parse_variable_name(input, &i);
			va = getenv(va); //TODO: should get from my own envv
			i -= (va != NULL);
			if (va)
				str_fjoin(&new_input, va);
			}
		}
		else
		{
			va = sub_until_chars(input, &i, "$\"'");
			new_input = str_join(
				(const char*)new_input,
				(const char*)va);
			sq = 0;//(input[i] == SINGLE_QT);
			dq = 0;//(input[i] == DOUBLE_QT);
			continue;
		}
		i++;
	}

	if (sq || dq)
		raise_error(env, ERR_SYNTAX);
	safe_free((void **)&env->input->line);
	env->input->line = new_input;
	env->input->len = str_len(new_input);
}
