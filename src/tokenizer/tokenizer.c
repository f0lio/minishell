
#include "minishell.h"

t_bool  tokenize_command(ENV, t_command **command)
{
    t_token     *token;
    t_command   *cmd;
    char        *line;
    int         i;

    cmd = *command;
    while (i < cmd->len)
    {
        if (line[i] == SPACE && ++i)
            continue ;
        if (line[i] == DOUBLE_QT || line[i] == SINGLE_QT)
            token = tokenize_quoted_command(env, cmd);
        else
            token = get_token(env, cmd);
        i = cmd->i;
        print(token->tok);
        push_back(&cmd->tokens, (void*)token);
        i++;
    }
    return 0;
}

t_bool  tokenize_commands(ENV)
{
    t_command   *cmd;
    t_node      *iter;
    int         ret;

    iter = env->commands;
    while (iter)
    {
        cmd = iter->data;
        ret = tokenize_command(env, &cmd);
        ret = lex_command(env, &cmd);
        if (ret)
            ;
        iter = iter->next;
    }
    return 0;
}