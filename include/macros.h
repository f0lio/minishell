#ifndef MACROS_H
# define MACROS_H

#include "minishell.h"

# define SHELL_NAME "minishell"

//Macrofication
# define FALSE          0
# define TRUE           1
# define NOT            ! // This is the python style !!
# define AND            && // This is the python style !!
# define OR             || // This is the python style !!
# define ELIF           else if // why not? // No need its not a clean code !!!

# define DIGITS         "0123456789"
# define ASCII_LOWER    "abcdefghijklmnopqrstuvwxyz"
# define ASCII_UPPER    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define PUNCTS         "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"
# define WHITESPACES    " \t\n\r\x0b\x0c"
# define SPACE          ' '
# define SINGLE_QT      '\''
# define DOUBLE_QT      '"'
# define BACK_SLASH     '\\'
# define EOL            '\n'
# define FLUSH          put_char('\n')
# define PASS           0; // !!

// BUFF_SIZE for get_next_line
# undef BUFF_SIZE
#  define BUFF_SIZE 1

//Max file descriptors that can be opened simultaneously
# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif

// 42 norminette: parameterized macros are forbidden

# define MALLOC(ptr)        (ptr) = malloc(sizeof(*(ptr) )) // No need also Not a clean code
# define ARRLLOC(p, l)      (p) = malloc(sizeof(*(p) ) * l) // SAME

# define IS_NUM(c)          (c >= '0' AND c <= '0') // SAME
# define IS_LOWER(c)        (c >= 'a' AND c <= 'z') // SAME
# define IS_UPPER(c)        (c >= 'A' AND c <= 'Z') // SAME
# define IS_ALPHA(c)        (IS_LOWER(c) OR IS_UPPER(c)) // SAME

# define ENV                t_env *env
# define LIST               t_node **list

//define signal codes


#endif
