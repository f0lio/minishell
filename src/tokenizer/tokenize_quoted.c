#include "minishell.h"

t_token	*tokenize_quoted_cmd(t_env *env, t_command *cmd)
{
	t_token	*token;

	if (env->input.line[env->input.i] == SINGLE_QT)
		token = tokenize_single_quoted(env, cmd);
	else
		token = tokenize_double_quoted(env, cmd);
	return (token);
}

t_token	*tokenize_single_quoted(t_env *env, t_command *cmd)
{
	t_token	*token;
	char	*tok;
	char	*line;
	int		j;

	line = cmd->cmd;
	j = env->input.i;
	while (++j < env->input.len)
		if (line[j] == SINGLE_QT && line[j - 1] != BACK_SLASH)
			break ;
	tok = sub_str(line, env->input.i + 1, j);
	token = new_token(tok);
	env->input.i = j;
	if (token)
		token->quoted = TYPE_SINGLE_QT;
	return (token);
}

t_token	*tokenize_double_quoted(t_env *env, t_command *cmd)
{
	t_token	*token;
	int		j;
	char	*line;

	line = cmd->cmd;
	j = env->input.i;
	while (++j < env->input.len)
		if (line[j] == DOUBLE_QT && line[j - 1] != BACK_SLASH)
			break ;
	token = new_token(sub_str(line, env->input.i + 1, j));
	env->input.i = j;
	if (token)
		token->quoted = TYPE_DOUBLE_QT;
	return (token);
}
