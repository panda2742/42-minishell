# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    variables.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 14:44:31 by ehosta            #+#    #+#              #
#    Updated: 2025/03/04 08:48:44 by ehosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE_DIR	:=	.make/
override	BUILD_DIR	:=	$(MAKE_DIR)$(shell git branch --show-current)/
override	MAKEFILES	:=	Makefile variables.mk
override	INCLUDES	:=	ft_array ft_base ft_fd ft_is ft_lst ft_math \
							ft_mem ft_misc ft_printf ft_str ft_to \
							get_next_line libft
override	HEADERS		:=	$(addprefix include/,$(addsuffix .h,$(INCLUDES)))
override	SRC_DIR		:=	src/
override	SRC_ARRAY	:=	ft_array_clear \
							ft_array_cpy \
							ft_array_fill \
							ft_array_getmax \
							ft_array_getmin \
							ft_array_getpos \
							ft_array_getsorted \
							ft_array_getval \
							ft_array_issorted \
							ft_array_new \
							ft_array_popint \
							ft_array_posdist \
							ft_array_prints \
							ft_array_pushint
override	SRC_FD		:=	ft_putchar_fd \
							ft_putendl_fd \
							ft_putnbr_base_fd \
							ft_putnbr_fd \
							ft_putptr_fd \
							ft_putstr_fd
override	SRC_FREE	:=	ft_free_inttab \
							ft_free_str \
							ft_free_strtab
override	SRC_GNL		:=	get_next_line
override	SRC_IS		:=	ft_isalnum \
							ft_isalpha \
							ft_isascii \
							ft_isdigit \
							ft_isincharset \
							ft_isprint \
							ft_issorted
override	SRC_LST		:=	ft_lstadd_back \
							ft_lstadd_front \
							ft_lstclear \
							ft_lstdelone \
							ft_lstiter \
							ft_lstlast \
							ft_lstmap \
							ft_lstnew \
							ft_lstsize
override	SRC_MATH	:=	ft_abs \
							ft_sign \
							ft_sqrt
override	SRC_MEM		:=	ft_bzero \
							ft_calloc \
							ft_memchr \
							ft_memcmp \
							ft_memcpy \
							ft_memmove \
							ft_memset
override	SRC_MISC	:=	ft_selection_sort
override	SRC_PRINTF	:=	ft_eprintf \
							ft_printf
override	SRC_STR		:=	ft_split \
							ft_strchr \
							ft_strdup \
							ft_striteri \
							ft_strjoin \
							ft_strlcat \
							ft_strlcpy \
							ft_strlen \
							ft_strlenc \
							ft_strmapi \
							ft_strncmp \
							ft_strnstr \
							ft_strrchr \
							ft_strtrim \
							ft_substr
override	SRC_TO		:=	ft_atoi \
							ft_itoa \
							ft_tolower \
							ft_toupper
override	SRCS		:=	$(addprefix array/,$(SRC_ARRAY)) \
							$(addprefix fd/,$(SRC_FD)) \
							$(addprefix free/,$(SRC_FREE)) \
							$(addprefix get_next_line/,$(SRC_GNL)) \
							$(addprefix is/,$(SRC_IS)) \
							$(addprefix lst/,$(SRC_LST)) \
							$(addprefix math/,$(SRC_MATH)) \
							$(addprefix mem/,$(SRC_MEM)) \
							$(addprefix misc/,$(SRC_MISC)) \
							$(addprefix printf/,$(SRC_PRINTF)) \
							$(addprefix str/,$(SRC_STR)) \
							$(addprefix to/,$(SRC_TO))
override	SRC			:=	$(addprefix $(SRC_DIR),$(addsuffix .c,$(SRCS)))
override	OBJ			:=	$(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC))
override	DEPS		:=	$(patsubst %.o,%.d,$(OBJ))
override	DIRS		:=	$(sort $(dir $(NAME) $(OBJ) $(DEPS)))

override	DEPFLAGS	:=	-MMD -MP
OFLAGS		:=	-O3
CFLAGS		:=	-Wall -Wextra -Werror $(DEPFLAGS)
ARFLAGS		:=	rcs
MAKEFLAGS	:=	--no-print-directory
RMFLAGS		:=	-rf
override	GCC		:=	gcc
override	RM		:=	rm
override	AR		:=	ar

override	_END		:=	\033[0;0m
override	_BOLD		:=	\033[0;1m
override	_UNDER		:=	\033[0;4m
override	_REV		:=	\033[0;7m
override	_ERASE		:=	\033[2K\r
override	_GREY		:=	\033[0;30m
override	_RED		:=	\033[0;31m
override	_GREEN		:=	\033[0;32m
override	_YELLOW		:=	\033[0;33m
override	_BLUE		:=	\033[0;34m
override	_PURPLE		:=	\033[0;35m
override	_CYAN		:=	\033[0;36m
override	_WHITE		:=	\033[0;37m
override	_IGREY		:=	\033[0;40m
override	_IRED		:=	\033[0;41m
override	_IGREEN		:=	\033[0;42m
override	_IYELLOW	:=	\033[0;43m
override	_IBLUE		:=	\033[0;44m
override	_IPURPLE	:=	\033[0;45m
override	_ICYAN		:=	\033[0;46m
override	_IWHITE		:=	\033[0;47m
