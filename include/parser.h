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

typedef struct		s_quote {
	short int		single_quote; // 1 or 0
	short int		double_quote; // 1 or 0
	size_t			num_quotes; // is it odd or even
}					t_quote;

typedef struct 		s_cmd
{
	char 			**arg;
	char			**filename;
	char 			separator;
	struct s_cmd	*next;
}					t_cmd;

typedef enum	e_my_bool {
	_false		= 0,
	_true		= !_false  // This is just for the compiler so that he takes care of false value based on the data type
}				t_boolean;


typedef enum			e_redirections {
	read_file			= 0,
	append_file			= 1,
	write_file			= 2
}						t_redirections;

typedef enum			e_separators {
	semicolone			= 0,
	pip					= 1
}						t_separators;

int					check_for_double_quote(char *line);
int					is_it_cmd(char *line);
int					parse_special_chars(char *line);
t_cmd				*parse_line(char *line, t_cmd *commands, t_redirections *redirections, t_separators *separators, t_quote *quotes);
int					check_special_operator(char *line);
t_redirections		*treat_redir(char *line, t_redirections *redirections);
t_separators		*treat_separator(char *line, t_separators *separator);
t_quote				*parse_quotes(char *line, t_quote *quotes);

#endif
