#include "minishell.h"

void     lex_commands(ENV)
{
    t_node *cmd;

    cmd = env->commands;
    while (cmd)
    {
        lex_cmd(env, (t_command*)cmd);
        cmd = cmd->next;
    }
}

void     lex_cmd(ENV, t_command *cmd)
{
    t_node *token;

    token = cmd->tokens;

    

    // I need meaning..!!
}
