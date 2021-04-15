
// #include "minishell.h"

// t_command       *get_quoted_command(ENV)
// {
//     t_command   *cmd;

//     if (env->input->line[env->input->i] == SINGLE_QT)
//         cmd = single_quoted_cmd(env);
//     else
//         cmd = double_quoted_cmd(env);
//     // if (cmd)
//     //     cmd->quoted = TRUE;
//     return (cmd);
//     //Should be cleaned from backSlashes..
// }

// t_command    *single_quoted_cmd(ENV)
// {
//     t_command   *cmd;
//     char        *line;
//     size_t      j;

//     cmd = new_cmd();
//     line = env->input->line;
//     j = env->input->i;
//     while (++j < env->input->len)
//     {
//         if (line[j] == SINGLE_QT && line[j - 1] != BACK_SLASH)
        
//         if (line[j] == SINGLE_QT && line[j - 1] != BACK_SLASH)
//         {
//             j++;
//             break;
//         }
//     }
//     cmd->cmd = sub_str(line, env->input->i, j);
//     env->input->i = j;
//     return (cmd);
// }

// t_command    *double_quoted_cmd(ENV)
// {
//     t_command   *cmd;


//     return cmd;
// }

// t_command       *get_command(ENV)
// {
//     t_command   *cmd;
//     char        *line;
//     int         j;

//     cmd = new_cmd();
//     j = env->input->i ;
//     line = env->input->line;
//     while (j < env->input->len)
//     {
//         if (line[j] == BACK_SLASH)
//             ;
//         else if (line[j] == ';' && line[j - 1] != BACK_SLASH)
//             break ;
//         j++;
//     }
//     cmd->cmd = sub_str(line, env->input->i, j);
//     env->input->i = j;
//     return cmd;
// }

// t_bool      split_commands(ENV)
// {
//     t_token     *token;
//     t_command   *cmd;
//     char        *line;
    
//     int     i;
//     int     j;

//     line = env->input->line;
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
//             push_back(&env->commands, cmd);
//         }
//         else
//             i++;
//     }

//     return 0;
// }

// // t_bool     split_commands(ENV)
// // {
// //     t_node      *iter;
// //     t_token     *token;
// //     t_command       *cmd;
// //     t_bool      flag;

// //     //Either this allocation, or tweaking new_node()
// //     MALLOC(env->commands);

// //     flag = FALSE;
// //     cmd = new_cmd();
// //     iter = env->tokens;
// //     while (iter)
// //     {
// //         token = iter->data;
// //         if (str_cmp(token->tok, ";")
// //             OR str_cmp(token->tok, "||"))
// //         {
// //             // print("ANOTHER ONE");
// //             push_back(&env->commands, cmd);
// //             // print("AFTER");
// //             cmd = new_cmd();
// //             flag = TRUE;
// //         }
// //         else if (str_cmp(token->tok, "&&"))
// //         {
// //             push_back(&env->commands, cmd);
// //             cmd = new_cmd();
// //             flag = TRUE;
// //         }
// //         else
// //         {
// //             push_back(&cmd->tokens, iter->data);
// //             flag = FALSE;
// //             // when there is no such SEP, add to commands list.
// //         }
// //         iter = iter->next;
// //     }
// //     return 0;
// // }
