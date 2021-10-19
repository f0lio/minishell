
#include "minishell.h"

t_command *create_command(t_node *tokens, int count)
{
    t_command   *cmd;
    int         i;

    cmd = new_cmd();
    if (!cmd)
        return NULL;
    cmd->tokens_count = count;
    cmd->tokens = create_tokens_array(tokens, count);
    return cmd;
}

# define    ARR_SIZE   256

t_token *get_token(ENV)
{
    t_token *token;
    t_array *skip;
    size_t  j;
    short   k;
    char    *line;

    BOOL flag = FALSE;

    //To handle:
    //  +[ cd d\ ir]
    //  -[echo okay \\ > file]
    //  -[echo okay \ > file]

    BOOL dq = 0, sq = 0;
    skip = new_array(ARR_SIZE);
    k = 0;
    j = env->input->i;
    line = env->input->line;
    j += skip_char(&line[j], SPACE);
    while (j < env->input->len)
    {
        if (j == 0 || (j > 0 && line[j - 1] != BACK_SLASH))
        {
            //haha branchlessness
            // sq += (((sq == 1 && dq != 1) | 1) * -1) * (line[j] == SINGLE_QT);
            // dq += (((dq == 1 && sq != 1) | 1) * -1) * (line[j] == DOUBLE_QT);
            // (line[j] == DOUBLE_QT) && (dq += (((dq == 1 && sq != 1) | 1) * -1));
            // (line[j] == SINGLE_QT) && (sq += (((sq == 1 && dq != 1) | 1) * -1));

            if (line[j] == SINGLE_QT)
            {
                if (sq == 1 && dq != 1) // single is not inside double
                    sq--;
                else
                    sq++;
            }
            else if (line[j] == DOUBLE_QT)
            {
                if (dq == 1 && sq != 1) // single is not inside double
                    dq--;
                else
                    dq++;
            }
        }
        //   'ec'h"o" 'ab cd' "ef" 'g"h"'
        if ((line[j] == SPACE || line[j] == SEP) && !sq && !dq)
        {
            flag = 1;
            break ;
        }
        if ((dq == 2 || sq == 2) && line[j] == SPACE)
        {
            flag = 2;
            break ;
        }
        j++;
    }
    token = new_token(clean_sub_str(line, env->input->i, j, skip));
    env->input->i = j;
    return token;
}

BOOL tokenize_input(ENV)
{
    t_token     *token;
    t_node      *tokens_list;
    t_node      *cmds_list;
    char        *line;
    int         i;

    int         tokens_count;

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
    return (0);
}
