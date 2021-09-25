
#include "minishell.h"

t_token **create_tokens_array(t_node *list, int size)
{
    t_token **tokens;
    t_token *token;
    t_node  *it;
    int     i;

    tokens = (t_token**)malloc(size * sizeof(t_token*));
    
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
