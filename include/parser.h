#ifndef __PARSER_H__
# define __PARSER_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct is_quote {
	short int 	single_quote; // 1 or 0
	short int 	double_quote; // 1 or 0
	size_t 		num_quotes; // is it odd or even
}				t_is_quote;

typedef enum	t_bool
{
	false = 0,
	true = !false  // This is just for the compiler so that he takes care of false value based on the data type
} 				bool;

int 		check_for_double_quote(char *line);
int 		is_it_cmd(char *line);
int 		parse_special_chars(char *line);

#endif
