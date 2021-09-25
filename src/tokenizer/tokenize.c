
#include "minishell.h"

# define ARR_SIZE 256

t_token *get_token(ENV, t_command *cmd)
{
    t_token *token;
    t_array *skip;
    size_t  j;
    short   k;
    char    *line;
    
    //To handle:
    //  +[ cd d\ ir]
    //  -[echo okay \\ > file]
    //  -[echo okay \ > file]

    skip = new_array(ARR_SIZE);
    k = 0;
    j = env->input->i + 1;
    line = cmd->cmd;
    while (j < env->input->len)
    {
        if (line[j] == BACK_SLASH)
            skip->arr[k++] = j;
        else if (line[j] == ' ' && line[j - 1] != BACK_SLASH)
            break ;
        j++;
    }
    token = new_token(clean_sub_str(line, env->input->i, j, skip));
    env->input->i = j;
    return token;
}

t_bool tokenize_cmd(ENV, t_command *cmd)
{
    t_token     *token;
    t_node      *list;
    char        *line;
    int         i;
    

    list = NULL;
    line = cmd->cmd;
    cmd->tokens_count = 0;
    i = 0;
    while (i < env->input->len)
    {
        env->input->i = i;
        if (line[i] != SPACE)
        {
            if (line[i] == DOUBLE_QT || line[i] == SINGLE_QT)
                token = tokenize_quoted_cmd(env, cmd);
            else
                token = get_token(env, cmd);
            i = env->input->i;
            push_back(&list, token);
            cmd->tokens_count++;
        }
        else
            i++;
    }
    // print_tokens(cmd->tokens);
    
    cmd->tokens = create_tokens_array(list, cmd->tokens_count);
    
    // test
    printf("###################\n");
    printf("# Tokens count: %d\n", cmd->tokens_count);
    printf("###################\n");
    i = 0;
    while (i < cmd->tokens_count)
    {
        printf("%2.2d: [%s]\n", i, cmd->tokens[i]->tok);
        i++;
    }
    printf("###################\n");
    return 0;
}

t_bool tokenize_commands(ENV)
{
    t_command   *cmd;
    int         i;

    i = 0;
    while (i < env->cmds_count)
    {
        cmd = env->commands[i];
        env->input->i = 0;
        env->input->len = str_len(cmd->cmd);
        tokenize_cmd(env, cmd);
        i++;
    }
    return 0;
}
