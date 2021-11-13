
#include "minishell.h"

t_command	*create_command(t_node *tokens, int count)
{
	t_command   *cmd;
	int		 i;

	cmd = new_cmd();
	if (!cmd)
		return NULL;
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
	line = env->input->line;
	j = env->input->i + skip_char(&line[env->input->i], SPACE) - 1;
	while (++j < env->input->len)
		if (quote == 0 && is_included(line[j], "|") && ++j)
			break ;
		else if (quote == 0 && is_included(line[j], "><") && ++j)
		{
			j += line[j] == line[j - 1];
			break ;
		}
		else if (line[j] == SINGLE_QT || line[j] == DOUBLE_QT)
		{
			if (line[j] == quote && ++j)
				break ;
			quote = line[j];
		}
		else if (!quote && is_included(line[j + 1], "|> <") && ++j)
			break ;
	token = new_token(sub_str(line, env->input->i, j));
	token->quoted = (quote != 0);
	env->input->i = j;
	return token;
}

BOOL tokenize_input(ENV)
{
	t_token	*token;
	t_node	*tokens_list;
	t_node	*cmds_list;
	char	*line;
	int		i;

	int		 tokens_count;

	tokens_count = 0;
	tokens_list = NULL;
	cmds_list = NULL;
	line = env->input->line;
	i = skip_char(line, ' ');
	if (line[i] == SEP)
		return raise_error(env, ERR_SYNTAX);
	while (i < env->input->len)
	{
		// if line[i] == B_SLASH => skip..?
		env->input->i = i;
		if (line[i] != SPACE)
		{
			if (line[i] == SEP)
			{
				push_back(
					&cmds_list,
					create_command(tokens_list, tokens_count));
				// destroy_list(&tokens_list);	
				tokens_list = NULL;
				tokens_count = 0;
				env->cmds_count++;
				i++;
				continue ;
			}
			// else if (line[i] == PIPE)
			// {
			// 	token = new_token(str_dup("|"));
			// 	push_back(&tokens_list, token);
			// 	i++;
			// 	continue ;
			// }
			// else if (line[i] == '>' || line[i] == '<')
			// {
			// 	;
			// }
			
			token = get_token(env);
			i = env->input->i;
			push_back(&tokens_list, token);
			tokens_count++;
		}
		else
			i++;
	}
	if (tokens_list)
	{
		push_back(
			&cmds_list, create_command(tokens_list, tokens_count));
		// destroy_list(&tokens_list);
		env->cmds_count++;
		tokens_list = NULL;
	}
	env->commands = create_commands_array(cmds_list, env->cmds_count);
	// free {tokens,cmds}_list
	return (0);
}
