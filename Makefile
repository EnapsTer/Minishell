NAME		= minishell
#####################################sources#######################################
SRC			= $(PARSE_EXE)\
			  $(EXECUTION_EXE)\
			  $(ENVIRONMENT_EXE)\
			  $(UTILS_EXE)\
			  main.c
#####################################parse#######################################
PARSER_PATH	= srcs/parsing/
PARSE_EXE	= $(PARSER_PATH)advanced_split.c\
			  $(PARSER_PATH)command_parsing.c
#####################################execution#################################
EXECUTION_PATH	= srcs/command_handlers/
EXECUTION_EXE	= $(EXECUTION_PATH)commands_handler.c\
				  $(EXECUTION_PATH)command_io.c\
				  $(EXECUTION_PATH)commands_execution.c
#####################################enviroment#######################################
ENVIRONMENT_PATH	= srcs/environment/
ENVIRONMENT_EXE	= $(ENVIRONMENT_PATH)environment_utils.c
#####################################utils#######################################
UTILS_PATH	= srcs/utils/
UTILS_EXE	= $(UTILS_PATH)advanced_split_utils.c\
			  $(UTILS_PATH)delimiter_comparators.c\
			  $(UTILS_PATH)commands_utils.c\
			  $(UTILS_PATH)strs_utils.c\
			  $(UTILS_PATH)command_io_utils.c
#####################################objects#######################################
OBJ			= $(SRC:.c=.o)
#####################################libft#######################################
L_PATH		= libft/
L_NAME		= libft.a
#####################################flags#######################################
CFLAGS		= -Wall -Wextra
SANITIZE	= -fsanitize=address
#####################################headers#######################################
INC			= includes/
HDR			= $(INC)minishell.h\
			  $(INC)libft.h\
			  $(INC)advanced_split.h\
			  $(INC)advanced_split_utils.h\
			  $(INC)strs_utils.h\
			  $(INC)delimiter_comparators.h\
			  $(INC)command_handlers.h\
			  $(INC)commands_parser.h\
			  $(INC)commands_utils.h\
			  $(INC)commands_execution.h\
			  $(INC)get_next_line.h\
			  $(INC)start.h\
			  $(INC)environment_utils.h

.c.o: $(HDR)
	gcc $(CFLAGS) -I$(INC) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ) $(HDR)
	make -C $(L_PATH)
	gcc $(CFLAGS) $(SANITIZE) $(L_PATH)$(L_NAME) $(OBJ) -o $(NAME)

all:  $(NAME)

clean:
	make clean -C $(L_PATH)
	rm -rf $(OBJ) 

fclean: clean
	rm -rf $(L_PATH)$(L_NAME)
	rm -rf $(NAME)

re: fclean all

norm: $(SRC)
	norminette $(SRC) $(HDR)

.PHONY: all clean fclean re