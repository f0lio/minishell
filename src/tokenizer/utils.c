
#include "minishell.h"

t_token *create_tokens_array(t_node *list, int size)
{
	t_token	*tokens;
	t_node	*it;
	t_node	*p;
	int		i;

	tokens = (t_token*)malloc(size * sizeof(t_token));
	if (!tokens)
		return NULL;
	i = 0;
	it = list;
	while (i < size && it)
	{
		tokens[i].tok = ((t_token*)it->data)->tok;
		tokens[i].type = ((t_token*)it->data)->type;
		tokens[i].len = ((t_token*)it->data)->len;
		tokens[i].order = ((t_token*)it->data)->order;
		tokens[i].quoted = ((t_token*)it->data)->quoted;	
		i++;
		p = it;
		it = it->next;
		safe_free((void **)&p->data);
		safe_free((void **)&p);
	}
	return tokens;
}

t_command *create_commands_array(t_node *list, int size)
{
	t_command	*cmds;
	t_node		*it;
	t_node		*p;
	int			i;

	cmds = (t_command*)malloc(size * sizeof(t_command));
	i = 0;
	it = list;
	while (i < size && it)
	{
		
		cmds[i].cmd = ((t_command*)it->data)->cmd;
		cmds[i].tokens = ((t_command*)it->data)->tokens;
		cmds[i].scmd = ((t_command*)it->data)->scmd;
		
		// cmds[i].origio = ((t_command*)it->data)->origio;
		
		cmds[i].tokens_count = ((t_command*)it->data)->tokens_count;
		cmds[i].tokarr = ((t_command*)it->data)->tokarr;
		cmds[i].pipe_count = ((t_command*)it->data)->pipe_count;
		cmds[i].pipe_location = ((t_command*)it->data)->pipe_location;
		cmds[i].ret = ((t_command*)it->data)->ret;
		cmds[i].sep = ((t_command*)it->data)->sep;
		
		i++;
		p = it;
		it = it->next;
		safe_free((void **)&p->data);
		safe_free((void **)&p);
	}
	return cmds;
}
