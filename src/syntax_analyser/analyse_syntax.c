#include "minishell.h"

BOOL	token_is(t_token *token, char *s)
{
	if (token->quoted)
		return (FALSE);
	return (str_cmp(token->tok, s));
}

BOOL	check_next_token(t_env *env, BOOL *flag, int len, t_command *cmd)
{
	int	j;

	j = -1;
	while (++j < len)
	{
		!(*flag) && ((*flag) += token_is(&cmd->tokens[j], "|"));
		!(*flag) && ((*flag) += token_is(&cmd->tokens[j], ">"));
		!(*flag) && ((*flag) += token_is(&cmd->tokens[j], ">>"));
		!(*flag) && ((*flag) += token_is(&cmd->tokens[j], "<"));
		!(*flag) && ((*flag) += token_is(&cmd->tokens[j], "<<"));
		!(*flag) && ((*flag) += token_is(&cmd->tokens[j], ";"));
		(*flag) && ((*flag) += token_is(&cmd->tokens[j + 1], "|"));
		(*flag) && ((*flag) += token_is(&cmd->tokens[j + 1], ">"));
		(*flag) && ((*flag) += token_is(&cmd->tokens[j + 1], ">>"));
		(*flag) && ((*flag) += token_is(&cmd->tokens[j + 1], "<"));
		(*flag) && ((*flag) += token_is(&cmd->tokens[j + 1], "<<"));
		(*flag) && ((*flag) += token_is(&cmd->tokens[j + 1], ";"));
		if (*flag == 2)
			return (raise_error(env, ERR_SYNTAX));
		*flag = FALSE;
	}
	return (0);
}

BOOL	analyse_syntax(t_env *env)
{
	int			i;
	int			len;
	t_command	*cmd;
	BOOL		flag;

	i = -1;
	while (++i < env->cmds_count)
	{
		cmd = &env->commands[i];
		len = cmd->tokens_count - 1;
		flag = FALSE;
		flag += token_is(&cmd->tokens[len], "|");
		flag += token_is(&cmd->tokens[len], "<");
		flag += token_is(&cmd->tokens[len], ">");
		if (flag)
			return (raise_error(env, ERR_SYNTAX));
		if (check_next_token(env, &flag, len, cmd))
			return (-1);
	}
	return (0);
}
