#include "minishell.h"

int     lex_tokens(ENV)
{
    t_token *token;
    t_node  *iter;

    iter = env->tokens;
    while (iter)
    {
        token = iter->data;

        //if tok == SEP -> new_cmd
        //if tok ==  -> new_cmd


        if (0)
        {

        }

        //BUILTIN / CMD
        //ARG
        //VAR
        //SEP ; | || & &&

        iter = iter->next;
    }
    return 0;
}