
.PHONEY: all clean fclean re bonus

NAME				= 	minishell
CC					=	clang
FLAGS				= 	-Werror -Wextra -Wall

UTILS				=	strtools_0.c strtools_1.c strtools_2.c strtools_3.c\
						file_tools.c get_line.c linked_list.c  destructors.c\
						error_handlers.c signals_handlers.c exit_handlers.c\
						itoa.c tmp_utils.c
						

CONSTRUCTORS		=	env.c
HISTORY				=	history.c 
TOKENIZER			=	tokenize.c\
						 command_checker.c\
						tokenize_quoted.c quotes_checker.c\
						utils.c
LEXER				=	lexer.c
PARSER				=	expansion.c helpers.c double_quoted_tokens.c escaping.c
EXECUTER			=	redirect.c\
						apex_strtools.c\
						pipe.c\
						builtins.c\
						tools.c

DBG					=	dbg_utils.c mem-limit.c

SRC					=	src/minishell.c\
						$(DBG:%.c=./dbg/%.c)\
						$(CONSTRUCTORS:%.c=./src/constructors/%.c)\
						$(TOKENIZER:%.c=./src/tokenizer/%.c)\
						$(LEXER:%.c=./src/lexer/%.c)\
						$(PARSER:%.c=./src/parser/%.c)\
						$(UTILS:%.c=./src/utils/%.c)\
						$(EXECUTER:%.c=./src/execution/%.c)\
						$(HISTORY:%.c=./src/history/%.c)

COMPILE	= $(CC) $(SRC) -I include -o $(NAME) -g #-I dbg #-fsanitize=address 

all: $(NAME)

$(NAME): $(SRC)
	@$(COMPILE)

run: all
	@./$(NAME)

clean:
	@rm -rf *.o

fclean: clean
	@-rm -f $(NAME)
	@-rm -f *.out
	@-rm -f *.gch
	@-rm -rf ./*.d*

re: fclean all

sandbox:
	@$(NAME)
	@sh ./start.sh