#include "minishell.h"

// Warning! This a black box! Don't try to read it. 

void expand_input(t_env *env)
{
	char    *va;
	char    *p;
	char    *new_input;
	char    *input;
	char    *buf;
	int     i;

	BOOL    dq;
	BOOL    sq;

	input = env->input->line;
	new_input = str_dup("");
	sq = 0 + (input[0] == SINGLE_QT);
	dq = 0 + (input[0] == DOUBLE_QT);
	i = 0;
	while (i < env->input->len)
	{
		printf("i: %d\n", i); usleep(8e5);
		if (i == 0 || input[i - 1] != BACK_SLASH)
		{
			sq += (input[i] == SINGLE_QT);
			dq += (input[i] == DOUBLE_QT);
			// printf("SQ: %d\n", sq);
			// printf("DQ: %d\n", dq);
		}

		if (sq)
		{
			printf("SINGLE: %d [%c]\n", i, input[i]);
			i += (input[i] == SINGLE_QT);
			va = sub_until_chars(input, &i, "'");
			str_fjoin(&new_input, va);
			i += (input[i] == SINGLE_QT);
			if (input[i] == SINGLE_QT)
				sq = FALSE;
		}
		else if (dq)
		{
			printf("DOUBLE: %d [%c]\n", i, input[i]);
			i += (input[i] == DOUBLE_QT);
			// 
			p = va;
			va = sub_until_chars(input, &i, "\"");
			va = expand_token(env, va);
			printf ("EXP [%s]\n", va);
			str_fjoin(&new_input, va);

			// i += str_len(va);
			printf("VA: %d [%s]\n", i, va);
			i += (input[i] == DOUBLE_QT);
			if (input[i] == DOUBLE_QT)
				dq = FALSE;
		}
		if (input[i] == DOLLAR && (i == 0 || input[i - 1] != BACK_SLASH))
		{
			printf("DOLLAR: %d [%c]\n", i, input[i]);
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
			printf("ELSE: %d [%c]\n", i, input[i]);
			if (sq)
			{
				va = sub_until_chars(input, &i, "\"'");
			}
			else
				va = sub_until_chars(input, &i, "$\"'");
			printf("VA: %d [%s]\n", i, va);
			new_input = str_join(
				(const char*)new_input,
				(const char*)va);
			sq = FALSE;
			dq = FALSE;
			// continue ;
		}
		i++;
	}
	if (sq || dq)
		raise_error(env, ERR_SYNTAX);
	if (env->input->line)
		free(env->input->line);
	env->input->line = new_input;
}

/* quick tests:
$USER"hi $USER$USER"-'$USER' ho$USER
*/
