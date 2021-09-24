
#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "minishell.h"

// main
int         repl(ENV);
int         read_input(char **input);
void        show_prompt(char *msg);

// Constructos
t_token         *new_token(char *tok);
t_array         *new_array(int size);
t_env           *init_env(int argc, char **argv, char **env_var);
t_token         **create_tokens_array(t_node *list, int size);

// Destructors 
void            reset_data(ENV);
void            destroy_command(void *command);
void            destroy_token(void *token);
void            safe_free(void **ptr);

// Tokenizer
t_bool          tokenize_commands(ENV);
t_bool          tokenize_cmd(ENV, t_command *cmd);
t_token         *get_token(ENV, t_command *cmd);
t_token         *tokenize_quoted_cmd(ENV, t_command *cmd);
t_token         *tokenize_single_quoted(ENV, t_command *cmd);
t_token         *tokenize_double_quoted(ENV, t_command *cmd);

// Commands
t_bool          split_commands(ENV);
t_command       *new_cmd(void);
t_command       *get_quoted_command(ENV);
t_command       *single_quoted_cmd(ENV);
t_command       *double_quoted_cmd(ENV);
t_command       *get_command(ENV);
t_bool          command_is_valid(ENV, t_command *cmd);

// Lexer
int             lex_tokens(ENV);

// strtools_0
size_t      str_len(const char *str);
void        put_char(char c);
void        put_str(const char *str);
void        fput_char(char c, int fd);
void        fput_str(const char *str, int fd);

// strtools_1
size_t      line_len(const char *str);
t_bool      find_eol(char *buff);
t_bool      line_isempty(char *line);
t_bool      str_cmp(char *s1, char *s2);
t_bool      str_ncmp(char *s1, char *s2, int max);
//char        *char_addr(char c, char **buff);

// strtools_2
char        *str_dup(const char *str);
char        *str_join(const char *s1, const char *s2);
char        *sub_str(
                    char const *s, int start, int end);
char        *clean_sub_str(
                    char const *s, int start, int end, t_array *arr );

// Quotes stuff
t_bool      check_quotes(char *str);
t_bool      check_quoted_str(char *str, char c);
t_bool      is_str_quoted(char *str, char mark);
t_bool      is_bad_quoted(char *str);



// Linked list functions
t_node      *new_node(void *data);
t_node      *get_n_node(t_node *lines, int index);
t_node      *push_back(LIST, void  *data);
void        push_front(LIST, void  *data);

size_t      list_size(t_node *list);
void        list_iter(LIST, void(*fun)(void *));
void        destroy_lst(LIST);
void        delete_lst(LIST);


// Parser
t_bool      split_by_type(char *buff, t_node **tokens);
int         tokenize(char *buff, ENV);

// Errors
t_bool      raise_error(ENV, char *msg);
void        destroy_env(ENV);

// File tools
t_bool      create_file(char *path);
t_bool      file_exists(char *path);
t_node      *read_lines(int fd);
int         get_line(int fd, char **line);
t_bool      write_line(int fd, char *line);
t_bool      write_lines(int fd, t_node *lines);

// History
t_bool      is_arrow(ENV);
t_bool      get_history(ENV);
t_bool      set_history(ENV);
void        saveto_history(ENV);

// Signal handlers
void	handle_interuption(int sig_code);
t_bool	is_ctrl_d(char *input);

// on exit
void    exit_program(ENV, int exit_code);


//temporary utils
void    print_array(t_array *arr, t_bool minus);
void    print_tokens(t_node *tokens);
void    print_linked_list(t_node *list);

#endif