
#include "minishell.h"

/* TODO:
**  On read_lines() function, read lines using get_line() function
**  get_line() is in get_line.c, which has a TODO.
*/
t_bool  create_file(char *path)
{
    int fd;

    fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd < 0)
        return FALSE;
    close(fd);
    return TRUE;
}

t_bool  file_exists(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return FALSE;
    close(fd);
    return TRUE;
}

/**
**  Reads a file and make doubly linked list from lines
** 
**  @param fd file descriptor to read from
**  @return Doubly_linked_list containing file lines
**/
t_node  *read_lines(int fd)
{
    t_node  *lines;
    char    *line;

    lines = NULL;

    // tmp block for testing purposes
    {
        #define MAX_LINE_LENGTH 1024
        FILE *file = fopen("./.minishell_history", "r");
        char *line = calloc(MAX_LINE_LENGTH, sizeof(char));
        while (fgets(line, MAX_LINE_LENGTH, file))
        {
            if (!line)
                break;
            push_back(&lines, str_dup(line));
            // free(line);
        }
    }
    return lines;
}

