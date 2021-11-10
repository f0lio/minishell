
#include "minishell.h"

BOOL	 token_is(t_token *token, char *s)
{
	if (token->quoted)
		return FALSE;
	return (str_cmp(token->tok, s));
}

BOOL	analyse_syntax(t_env *env)
{
	int			len;
	t_command	*cmd;
	BOOL		flag;

	for (size_t i = 0; i < env->cmds_count; i++)
	{
		cmd = env->commands[i];
		len = cmd->tokens_count - 1;
		flag = FALSE;
		flag += token_is(cmd->tokens[len], "|");
		flag += token_is(cmd->tokens[len], "<");
		flag += token_is(cmd->tokens[len], ">");
		if (flag)
			return raise_error(env, ERR_SYNTAX);
		for (size_t j = 0; j < len; j++)
		{
			!flag && (flag += token_is(cmd->tokens[j], "|"));
			!flag && (flag += token_is(cmd->tokens[j], ">"));
			!flag && (flag += token_is(cmd->tokens[j], ">>"));
			!flag && (flag += token_is(cmd->tokens[j], "<"));
			!flag && (flag += token_is(cmd->tokens[j], "<<"));
			!flag && (flag += token_is(cmd->tokens[j], ";"));
			flag && (flag += token_is(cmd->tokens[j + 1], "|"));
			flag && (flag += token_is(cmd->tokens[j + 1], ">"));
			flag && (flag += token_is(cmd->tokens[j + 1], ">>"));
			flag && (flag += token_is(cmd->tokens[j + 1], "<"));
			flag && (flag += token_is(cmd->tokens[j + 1], "<<"));
			flag && (flag += token_is(cmd->tokens[j + 1], ";"));
			if (flag == 2)
				return raise_error(env, ERR_SYNTAX);
			flag = FALSE;
		}
	}
	return 0;
}
