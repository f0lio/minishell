
#include "../../include/minishell.h"


void    print_array(t_array *arr, t_bool minus)
{
    if (minus)  
        for (size_t i = 0; i < arr->size && arr->arr[i] != -1; i++)
            DN(arr->arr[i]);
    else
        for (size_t i = 0; i < arr->size; i++)
            DN(arr->arr[i]);
}

void    print_tokens(t_node *tokens_list)
{
    t_node  *iter;
    t_token *token;

    iter = tokens_list;  //head
    while (iter)
    {
        token = (t_token*)iter->data;
        printf("@> [%s]\n", (char*)(token->tok));
        iter = iter->next;
    }
}
