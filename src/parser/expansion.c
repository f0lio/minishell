#include "minishell.h"

char 	*get_new_input(t_env *env, BOOL	*sq, BOOL *dq)
{
	char	*new_input;
	char	*input;
	int		i;

	new_input = str_dup("");
	input = env->input->line;
	i = 0;
	while (i < env->input->len)
	{
		if (i == 0 || input[i - 1] != BACK_SLASH)
		{
			*sq +=  (input[i] == SINGLE_QT);
			*dq +=  (input[i] == DOUBLE_QT);
		}
		if (*sq)
			*sq = handle_sinqle_quote(input, &new_input, &i);
		else if (*dq)
			*dq = handle_double_quote(env, input, &new_input, &i);
		if (input[i] == DOLLAR && (i == 0 || input[i - 1] != BACK_SLASH))
			handle_unquoted_dollar(input, &new_input, &i);
		else
		{
			handle_unquoted_token(input, &new_input, &i);
			*sq = FALSE;
			*dq = FALSE;
			continue ;
		}
		i++;
	}
	return (new_input);
}

void expand_input(t_env *env)
{
	char	*new_input;
	BOOL	dq;
	BOOL	sq;

	dq = 0;
	sq = 0;
	new_input = get_new_input(env, &sq, &dq);
	if (sq || dq)
		raise_error(env, ERR_SYNTAX);
	safe_free((void **)&env->input->line);
	env->input->line = new_input;
	env->input->len = str_len(new_input);
}
