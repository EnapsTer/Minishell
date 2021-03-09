NAME		= minishell
#####################################sources#######################################
SRC			= $(PARSE_EXE)\
			  $(EXECUTION_EXE)\
			  $(ENVIRONMENT_EXE)\
			  $(UTILS_EXE)\
			  $(READ_EXE)\
			  $(BUILT_EXE)\
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
ENVIRONMENT_EXE	= $(ENVIRONMENT_PATH)environment_utils.c\
				  $(ENVIRONMENT_PATH)initialization_logic.c
#####################################utils#######################################
UTILS_PATH	= srcs/utils/
UTILS_EXE	= $(UTILS_PATH)advanced_split_utils.c\
			  $(UTILS_PATH)delimiter_comparators.c\
			  $(UTILS_PATH)commands_utils.c\
			  $(UTILS_PATH)strs_utils.c\
			  $(UTILS_PATH)command_io_utils.c
#####################################reading#######################################
READ_PATH	= srcs/command_read/
READ_EXE	= $(READ_PATH)read_utils.c\
			  $(READ_PATH)core_logic.c\
			  $(READ_PATH)syntax_utils.c\
			  $(READ_PATH)remove_quoted_str.c\
			  $(READ_PATH)errors_read.c\
			  $(READ_PATH)signals.c\
			  $(READ_PATH)handle_new_line.c\
			  $(READ_PATH)syntax_logic.c
#####################################builtins#######################################
BUILT_PATH	= srcs/builtins/
BUILT_EXE	= $(BUILT_PATH)env.c\
			  $(BUILT_PATH)pwd.c\
			  $(BUILT_PATH)cd.c\
			  $(BUILT_PATH)export.c\
			  $(BUILT_PATH)unset.c\
			  $(BUILT_PATH)export_utils.c\
			  $(BUILT_PATH)echo.c\
			  $(BUILT_PATH)exit.c

#####i################################objects#######################################
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

all: $(NAME)

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
