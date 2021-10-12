#include "minishell.h"


void expand_command_tokens(t_env *env)
{
    int i;
    int j;

    i = -1;
    while (++i < env->cmds_count)
    {
        j = -1;
        while (++j < env->commands[i]->tokens_count)
            expand_tokens(env, env->commands[i]->tokens[j]);
    }
}

BOOL is_alphanum(char c)
{
    if (c <= 'z' && c >= 'a')
        return TRUE;
    if (c <= 'Z' && c >= 'A')
        return TRUE;
    if (c <= '9' && c >= '0')
        return TRUE;
    return FALSE;
}

void expand_tokens(t_env *env, t_token *token)
{
    char    *var;
    char    *value;
    char    *new_tok;
    int     i;
    int     start;

    if (token->quoted != TYPE_DOUBLE_QT)
        return ;
    i = 0;
    while (token->tok[i])
    {
        if (token->tok[i] == '$')
        {
            i++;
            start = i;
            while (is_alphanum(token->tok[i]) || token->tok[i] == '_')
                i++;
            // printf("-> [%d]: [%d]\n", start, i);
            var = sub_str(token->tok, start, i);
            value = getenv(var);
            // printf("[%s]: [%s]\n", var, value);
        }
        i++;
    }
    // value = getenv("");
}
