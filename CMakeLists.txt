cmake_minimum_required(VERSION 3.17)
project(minishell_project C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall") #add -Werror
include_directories(libft srcs includes)

set(BUILTINS_EXE srcs/builtins/echo.c srcs/builtins/pwd.c srcs/builtins/cd.c srcs/builtins/env.c srcs/builtins/exit.c srcs/builtins/export.c srcs/builtins/unset.c)
set(EXECUTION_EXE srcs/command_handlers/commands_handler.c srcs/command_handlers/command_io.c srcs/command_handlers/commands_execution.c)
set(COMMANDS_READ_EXE srcs/command_read/remove_quoted_str.c srcs/command_read/core_logic.c srcs/command_read/errors_read.c srcs/command_read/handle_new_line.c srcs/command_read/read_utils.c srcs/command_read/signals.c srcs/command_read/syntax_utils.c srcs/command_read/syntax_logic.c)
set(ENVIRONMENT_EXE srcs/environment/environment_utils.c srcs/environment/initialization_logic.c)
set(PARSE_EXE srcs/parsing/advanced_split.c srcs/parsing/command_parsing.c)
set(UTILS_EXE srcs/utils/advanced_split_utils.c srcs/utils/delimiter_comparators.c srcs/utils/commands_utils.c srcs/utils/command_io_utils.c srcs/utils/strs_utils.c)
set(INCLUDES includes/start.h includes/minishell.h includes/libft.h includes/advanced_split.h includes/advanced_split_utils.h includes/strs_utils.h includes/delimiter_comparators.h includes/command_handlers.h includes/commands_parser.h includes/commands_utils.h includes/commands_execution.h includes/environment_utils.h)

add_subdirectory(libft)

add_executable(minishell_project main.c ${INCLUDES} ${PARSE_EXE} ${UTILS_EXE} ${ENVIRONMENT_EXE} ${EXECUTION_EXE} ${BUILTINS_EXE} ${COMMANDS_READ_EXE})

target_link_libraries(minishell_project libft)