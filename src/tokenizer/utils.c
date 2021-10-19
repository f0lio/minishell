
#include "minishell.h"

t_token **create_tokens_array(t_node *list, int size)
{
    t_token **tokens;
    t_node  *it;
    int     i;

    tokens = (t_token**)malloc(size * sizeof(t_token*));
    if (!tokens)
        return NULL;
    i = 0;
    it = list;
    while (i < size && it)
    {
        tokens[i] = (t_token*)it->data;
        i++;
        it = it->next;
    }
    return tokens;
}

t_command **create_commands_array(t_node *list, int size)
{
    t_command   **cmds;
    t_node      *it;
    int         i;

    cmds = (t_command**)malloc(size * sizeof(t_command*));
    i = 0;
    it = list;
    while (i < size && it)
    {
        cmds[i] = (t_command*)it->data;
        i++;
        it = it->next;
    }
    return cmds;
}
