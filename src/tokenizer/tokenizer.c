#include "minishell.h"

void	add_new_cmd(
	t_env *env, t_node **cmds_list, t_node **tokens_list, int *tokens_count)
{
	env->cmds_count++;
	env->input.i++;
	push_back(
		cmds_list, create_command(*tokens_list, *tokens_count));
	(*tokens_count) = 0;
}

void	add_new_token(
	t_env *env, t_node **tokens_list, int *tokens_count)
{
	t_token	*token;
	char	*line;

	line = NULL;
	token = get_token(env, line);
	clean_from_quotes(token);
	push_back(tokens_list, token);
	(*tokens_count)++;
}

void	tokenizer(t_env *env, t_node **cmds_list, t_node **tokens_list)
{
	int	tokens_count;

	tokens_count = 0;
	while (env->input.i < env->input.len)
	{
		if (env->input.line[env->input.i] != SPACE)
			add_new_token(
				env, tokens_list, &tokens_count);
		else
			env->input.i++;
	}
	if (tokens_list)
		add_new_cmd(env, cmds_list, tokens_list, &tokens_count);
}

BOOL	tokenize_input(t_env *env)
{
	t_node	*tokens_list;
	t_node	*cmds_list;

	if (env->input.len == 0)
	{
		env->cmds_count = 0;
		return (0);
	}
	env->input.i = skip_char(env->input.line, ' ');
	if (env->input.line[env->input.i] == CMD_SEP)
		return (raise_error(env, ERR_SYNTAX));
	tokens_list = NULL;
	cmds_list = NULL;
	tokenizer(env, &cmds_list, &tokens_list);
	env->commands = create_commands_array(cmds_list, env->cmds_count);
	return (0);
}
