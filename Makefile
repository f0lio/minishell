.PHONEY: all clean fclean re bonus

NAME			= 	minishell
CC				=	clang
FLAGS			= 	-Werror -Wextra -Wall

#Source Files
UTILS			=	tmp_utils.c \
					strtools_0.c strtools_1.c strtools_2.c strtools_3.c\
					linked_list.c
					#num_tools_0.c\
					#get_line.c \
					#bintree.c

CONSTRUCTORS	=	env.c
TOKENIZER		=	commands_splitter.c quotes_checker.c tokenize.c
LEXER			=	lexer.c
PARSER			=	parser.c
EXECUTER		=	

DBG				=	MY_DBG.C

SRC				=	src/minishell.c\
					$(TOKENIZER:%.c=./src/tokenizer/%.c)\
					$(LEXER:%.c=./src/lexer/%.c)\
					$(PARSER:%.c=./src/parser/%.c)\
					$(UTILS:%.c=./src/utils/%.c)\
					$(CONSTRUCTORS:%.c=./src/constructors/%.c)

OBJ				=	minishell.o\
					$(TOKENIZER:.c=.o)\
					$(LEXER:.c=.o)\
					$(PARSER:.c=.o)\
					$(UTILS:.c=.o)\
					$(CONSTRUCTORS:.c=.o)

## For debuging:
DBG_FLAGS		=  -I dbg

###################

COMPILE	= $(CC) -I include -c $(SRC) -g #$(DBG_FLAGS)
LINK = $(CC) $(OBJ) -o $(NAME)  #$(DBG_FLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILE)
	@$(CC) $(OBJ) -Iinclude -o $(NAME)

$(OBJ): $(SRC)
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

bu: fclean
	@bash git_bu.sh
