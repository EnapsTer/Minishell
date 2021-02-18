cmake_minimum_required(VERSION 3.17)
project(Libft)

set(CMAKE_C_STANDARD 99)

set(LIBFT_EXE ft_atoi.c
        ft_bzero.c
        ft_calloc.c
        ft_isalnum.c
        ft_isalpha.c
        ft_isascii.c
        ft_isdigit.c
        ft_isprint.c
        ft_itoa.c
        ft_lstadd_back.c
        ft_lstadd_front.c
        ft_lstclear.c
        ft_lstdelone.c
        ft_lstiter.c
        ft_lstlast.c
        ft_strcmp.c
        ft_lstmap.c
        ft_lstnew.c
        ft_lstsize.c
        ft_memccpy.c
        ft_memchr.c
        ft_memcmp.c
        ft_memccpy.c
        ft_memmove.c
        ft_memset.c
        ft_putnbr_fd.c
        ft_putendl_fd.c
        ft_putchar_fd.c
        ft_putstr_fd.c
        ft_split.c
        ft_strchr.c
        ft_strdup.c
        ft_strjoin.c
        ft_strlcat.c
        ft_strlcpy.c
        ft_strlen.c
        ft_strmapi.c
        ft_strncmp.c
        ft_strnstr.c
        ft_strrchr.c
        ft_strtrim.c
        ft_substr.c
        ft_tolower.c
        ft_toupper.c
        get_next_line.c
        get_next_line.h
        get_next_line_utils.c
        ft_strcnt.c
        libft.h)

add_library(libft STATIC ${LIBFT_EXE})