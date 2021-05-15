
#include "minishell.h"

/* TODO:
**  -if file creation failed, choose a different path.
*/
t_bool  set_history(ENV)
{
    t_file *history;
    t_bool ret;

    ret = TRUE;
    history = env->history;
    history->path = ".minishell_history";
    if (!file_exists(history->path))
        ret = create_file(history->path);
    if (ret == FALSE)
    {
        print("READ TODO ON history.c");
        exit(EXIT_FAILURE);
    }
    history->fd = open(history->path, O_RDONLY);
    history->lines = read_lines(history->fd);
    // print_linked_list(history->lines);
    close(history->fd);
    return 0;
}

void  saveto_history(ENV)
{
    int fd;

    push_back(&env->history->lines, env->input);
    fd = open(env->history->path, O_APPEND | O_WRONLY);
    write_line(fd, env->input->line);
    write(fd, "\n", 1);
    close(fd);
}


t_bool  is_arrow(ENV)
{
    if (str_cmp(env->input->line, "UP"))
        return TRUE;
    return FALSE;
}

t_bool  get_history(ENV)
{
    return 0;
}


void    print_linked_list(t_node *list)
{
    for (t_node *iter = list; iter; iter = iter->next)
        print(iter->data);
}