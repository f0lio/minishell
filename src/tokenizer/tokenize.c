
#include "minishell.h"

# define ARR_SIZE 256

/* NOTE: 
**  -The following function will handle semicolons as well.
     When it finds one, with no active quotation mark, it will
     call create_command()
*/

t_token *get_token(ENV, t_command *cmd)
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
    line = cmd->cmd;
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
        if (line[j] == SPACE && !sq && !dq)
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

BOOL tokenize_cmd(ENV, t_command *cmd)
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
        // if line[i] == B_SLASH => skip..?
        env->input->i = i;
        if (line[i] != SPACE)
        {
            token = get_token(env, cmd);
            i = env->input->i;
            push_back(&list, token);
            cmd->tokens_count++;
        }
        else
            i++;
    }
    cmd->tokens = create_tokens_array(list, cmd->tokens_count);
    // destroy_list(&list);
    return 0;
}

BOOL tokenize_commands(ENV)
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
