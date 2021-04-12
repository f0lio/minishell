#ifndef __PARSER_H__
# define __PARSER_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

# define DIGITS         "0123456789"
# define ASCII_LOWER    "abcdefghijklmnopqrstuvwxyz"
# define ASCII_UPPER    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define PUNCTS         "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"
# define WHITESPACES    " \t\n\r\x0b\x0c"

typedef struct s_quote {
	short int 	single_quote; // 1 or 0
	short int 	double_quote; // 1 or 0
	size_t 		num_quotes; // is it odd or even
}				t_quote;

typedef struct 			s_cmd
{
	char 				**arg;
	char				**filename;
	char 				separator;
	struct s_cmd 		*next;
}						t_cmd;

typedef enum	e_my_bool {
	false = 0,
	true = !false  // This is just for the compiler so that he takes care of false value based on the data type
} 				bool;

int 		check_for_double_quote(char *line);
int 		is_it_cmd(char *line);
int 		parse_special_chars(char *line);
t_cmd		*parse_line(char *line, t_cmd *commands);
int			check_special_operator(char *line);

#endif
