
// #include "minishell.h"


// /* NOTE: 
// **  -This file is going to be removed. As the commands splitting
//       will happen on the tokenizer itself.
// */

// t_command *get_quoted_command(ENV)
// {
//     t_command *cmd;

//     if (env->input->line[env->input->i] == SINGLE_QT)
//         cmd = single_quoted_cmd(env);
//     else
//         cmd = double_quoted_cmd(env);
//     // if (cmd)
//     //     cmd->quoted = TRUE;
//     return (cmd);
//     //Should be cleaned from backSlashes..
// }

// t_command *single_quoted_cmd(ENV)
// {
//     t_command *cmd;
//     char *line;
//     size_t j;
//     t_bool found;

//     line = env->input->line;
//     found = FALSE;
//     j = env->input->i;
//     while (++j < env->input->len)
//     {
//         if (line[j] == SINGLE_QT && line[j - 1] != BACK_SLASH)
//         {
//             found = TRUE;
//             j++;
//             break;
//         }
//     }
//     if (!found)
//         return NULL;
//     cmd = new_cmd();
//     cmd->cmd = sub_str(line, env->input->i, j);
//     env->input->i = j;
//     return (cmd);
// }

// t_command *double_quoted_cmd(ENV)
// {
//      t_command *cmd;
//     char *line;
//     size_t j;
//     t_bool found;

//     line = env->input->line;
//     found = FALSE;
//     j = env->input->i;
//     while (++j < env->input->len)
//     {
//         if (line[j] == DOUBLE_QT && line[j - 1] != BACK_SLASH)
//         {
//             found = TRUE;
//             j++;
//             break;
//         }
//     }
//     if (!found)
//         return NULL;
//     cmd = new_cmd();
//     cmd->cmd = sub_str(line, env->input->i, j);
//     env->input->i = j;
//     return (cmd);
// }

// t_command   *get_command(ENV)
// {
//     t_command   *cmd;
//     char        *line;
//     int         j;

//     line = env->input->line;
//     j = env->input->i;
//     if (line[j] == ';')
//         return NULL;
//     while (j < env->input->len)
//     {
//         if (line[j] == BACK_SLASH && line[j - 1] == BACK_SLASH)
//             ;
//         else if (line[j] == BACK_SLASH && line[j - 1] == BACK_SLASH)
//             ;
//         else if (line[j] == ';' && line[j - 1] != BACK_SLASH)
//             break;
//         j++;
//     }
//     cmd = new_cmd();
//     cmd->cmd = sub_str(line, env->input->i, j);
//     env->input->i = j + 1;
//     return cmd;
// }

// BOOL split_commands(ENV)
// {
//     t_token     *token;
//     t_command   *cmd;
//     t_node      *list;
//     char        *line;
//     int         i;

//     list = NULL;
//     line = env->input->line;
//     env->cmds_count = 0;
//     i = 0;
//     while (i < env->input->len)
//     {
//         env->input->i = i;
//         if (line[i] != SPACE)
//         {
//             if (line[i] == DOUBLE_QT || line[i] == SINGLE_QT)
//                 cmd = get_quoted_command(env);
//             else
//                 cmd = get_command(env);
//             i = env->input->i;
//             if (command_is_valid(env, cmd))
//             {
//                 push_back(&list, cmd);
//                 env->cmds_count++;
//             }
//             else
//                 return raise_error(env, ERR_SYNTAX);
//         }
//         else
//             i++;
//     }
//     env->commands = create_commands_array(list, env->cmds_count);
//     return 0;
// }


#include "minishell.h"

