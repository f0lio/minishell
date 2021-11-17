
#include "minishell.h"

t_command	*create_command(t_node *tokens, int count)
{
	t_command	*cmd;
	int			i;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	cmd->tokens_count = count;
	cmd->tokens = create_tokens_array(tokens, count);
	return cmd;
}

t_token *get_token(ENV)
{
	t_token		*token;
	size_t		j;
	char		*line;
	char		quote;

	quote = 0;
	line = env->input.line;
	j = env->input.i + skip_char(&line[env->input.i], SPACE) - 1;
	while (++j < env->input.len)
		if (quote == 0 && is_included(line[j], "|") && ++j)
			break ;
		else if (quote == 0 && is_included(line[j], "><") && ++j)
		{
			j += line[j] == line[j - 1];
			break ;
		}
		else if (line[j] == SINGLE_QT || line[j] == DOUBLE_QT) // "hi ' X "
		{
			if (line[j] == quote && ++j)
				break ;
			if (quote == 0)
				quote = line[j];
		}
		else if (!quote && is_included(line[j + 1], "|> <") && ++j)
			break ;
	token = new_token(sub_str(line, env->input.i, j));
	if (token == NULL)
		return (NULL);
	token->quoted = (quote != 0);
	env->input.i = j;
	return token;
}

void	add_new_cmd(
	ENV, t_node **cmds_list, t_node **tokens_list, int *tokens_count)
{
	env->cmds_count++;
	env->input.i++;

	push_back(
		cmds_list,
		create_command(*tokens_list, *tokens_count));	
	(*tokens_count) = 0;
}


void	add_new_token(
	ENV, t_node **tokens_list, int *tokens_count)
{
	push_back(tokens_list, get_token(env));
	(*tokens_count)++;
}

void	tokenizer(ENV,t_node **cmds_list, t_node **tokens_list)
{
	int		 tokens_count;
	t_token	*token;

	tokens_count = 0;
	while (env->input.i < env->input.len)
	{
		if (env->input.line[env->input.i] != SPACE)
		{
			if (env->input.line[env->input.i] == CMD_SEP)
				add_new_cmd(
					env, cmds_list, tokens_list, &tokens_count);
			else
				add_new_token(
					env, tokens_list, &tokens_count);
		}
		else
			env->input.i++;
	}
	if (tokens_list)
		add_new_cmd(env, cmds_list, tokens_list, &tokens_count);
}

BOOL tokenize_input(ENV)
{
	t_node	*tokens_list;
	t_node	*cmds_list;

	env->input.i = skip_char(env->input.line, ' ');
	if (env->input.line[env->input.i] == CMD_SEP)
		return raise_error(env, ERR_SYNTAX);
	tokens_list = NULL;
	cmds_list = NULL;
	tokenizer(env, &cmds_list, &tokens_list);
	env->commands = create_commands_array(
						cmds_list,
						env->cmds_count);
	// {
	// 	t_node *it = cmds_list;
	// 	t_command *cmd;

	// 	while (it)
	// 	{
	// 		cmd = (t_command*)it;
	// 		printf("[%p]\n", cmd);
	// 		printf("[%s]\n", cmd->tokens[0].tok);
	// 		it = it->next;
	// 	}
	// 	list_iter(&cmds_list, destroy_command);
	// 	delete_list(&cmds_list);

	// }
	return (0);
}
