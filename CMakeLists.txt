cmake_minimum_required(VERSION 3.17)
project(minishell_project C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall") #add -Werror
include_directories(libft srsc includes)

set(PARSE_EXE srsc/parsing/advanced_split.c srsc/parsing/command_parsing.c)
set(EXECUTION_EXE srsc/command_handlers/commands_handler.c srsc/command_handlers/command_io.c srsc/command_handlers/commands_execution.c)
set(ENVIRONMENT_EXE srsc/environment/environment_utils.c)
set(UTILS_EXE srsc/utils/advanced_split_utils.c srsc/utils/delimiter_comparators.c srsc/utils/commands_utils.c srsc/utils/command_io_utils.c)
set(INCLUDES includes/minishell.h includes/libft.h includes/advanced_split.h includes/advanced_split_utils.h srsc/utils/strs_utils.c includes/strs_utils.h includes/delimiter_comparators.h includes/command_handlers.h includes/commands_parser.h includes/commands_utils.h includes/commands_execution.h includes/environment_utils.h)

add_subdirectory(libft)

add_executable(minishell_project ${INCLUDES} ${PARSE_EXE} ${UTILS_EXE} ${ENVIRONMENT_EXE} ${EXECUTION_EXE} main.c)

target_link_libraries(minishell_project libft)