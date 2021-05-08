#ifndef MACROS_H
#define MACROS_H
#include "minishell.h"
#undef BUFF_SIZE
#define BUFF_SIZE 32
#ifndef OPEN_MAX
#define OPEN_MAX 512
#endif
#define SHELL_NAME "minishell"
#define DIGITS "0123456789"
#define ASCII_LOWER "abcdefghijklmnopqrstuvwxyz"
#define ASCII_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define PUNCTS "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"
#define WHITESPACES " \t\n\r\x0b\x0c"
#define SPACE ' '
#define SINGLE_QT '\''
#define DOUBLE_QT '"'
#define BACK_SLASH '\\'
#define EOL '\n'
#define SEP ';'
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
/*
**
*/
#define FALSE 0
#define TRUE 1
#define FLUSH write(1, '\n', 1)
#define PASS 0;

//!!! 42 norminette: parameterized macros are forbidden
#define MALLOC(ptr) (ptr) = malloc(sizeof(*(ptr)))
#define ARRLLOC(p, l) (p) = malloc(sizeof(*(p)) * l)
#define IS_NUM(c) (c >= '0' && c <= '0')
#define IS_LOWER(c) (c >= 'a' && c <= 'z')
#define IS_UPPER(c) (c >= 'A' && c <= 'Z')
#define IS_ALPHA(c) (IS_LOWER(c) || IS_UPPER(c))
#define ENV t_env *env
#define LIST t_node **list

//Error messages, prefix macros with "ERR_"
#define ERR_MALLOC "Couldn't allocate memory"
#define ERR_SYNTAX "invalid syntax"

//define signal codes

#endif
