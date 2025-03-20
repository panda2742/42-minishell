# The name of the built executable
NAME					:=	minishell
# The directory where the built files will be
MAKE_DIR				:=	.make/

# The header files of the project
override	HDRS		:=	minishell
# The C source code files of the project
override	BUILTINS	:=	cd echo env exit export pwd unset
override	ENV			:=	create_env free_env get_var
override	ERRORS		:=	error_handler
override	EXEC		:=	exec
override	PROMPT		:=	show_prompt
override	SRCS		:=	main \
							$(addprefix builtins/builtins_,$(BUILTINS)) \
							$(addprefix env_manager/,$(ENV)) \
							$(addprefix errors/,$(ERRORS)) \
							$(addprefix exec/,$(EXEC)) \
							$(addprefix prompt/,$(PROMPT))

# The subdirectory where the built objects will be, for example ./make/minishell_develop/
override	BUILD_DIR	:=	$(MAKE_DIR)$(NAME)_$(shell git branch --show-current)/
# The header files directory
override	HDR_DIR		:=	include/
# The formatted version of the headers (with directory and extension), for example include/minishell.h
override	HDR			:=	$(addprefix $(HDR_DIR),$(addsuffix .h,$(HDRS)))
# The C source code files directory
override	SRC_DIR		:=	src/
# The formatted version of the C source code files (with directory and extension), for example src/main.c
override	SRC			:=	$(addprefix $(SRC_DIR),$(addsuffix .c,$(SRCS)))
# The libft submodule directory
override	LIBFT_DIR	:=	lib/
# The libft executable path
override	LIBFT		:=	$(LIBFT_DIR)libft.a
# Every object for each C source code file
override	OBJ			:=	$(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC))
# Every dep file (.d) for each C source code file
override	DEPS		:=	$(patsubst %.o,%.d,$(OBJ))
# All the required directories for the build of the project
override	DIRS		:=	$(sort $(dir $(NAME) $(OBJ) $(LIBFT) $(DEPS)))

# The C compilation flags
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP -g3
# The Makefile flags to hide the current directory on compilation
MAKEFLAGS	:=	--no-print-directory
# The compiler binary 
GCC			:=	cc
# The rm command used to remove some things
RM			:=	rm -r

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(BUILD_DIR)%.o: $(SRC_DIR)%.c Makefile $(HDR) | $(DIRS)
	$(CC) $(CFLAGS) -c -I$(LIBFT_DIR)/include -I$(HDR_DIR) $< -o $@

$(LIBFT): libft

.PHONY: libft
libft: force
	$(MAKE) -C $(LIBFT_DIR) all

.PHONY: force
force:
	@true

.PHONY: bonus
bonus: all

.PHONY: clean
clean:
	$(RM) $(MAKE_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: re
re:	 fclean
	$(MAKE)

$(DIRS):
	@mkdir -p $@

.PHONY: norm
norm:
	@norminette $(SRC_DIR) include/ $(LIBFT_DIR)/ | grep "Error"

.PHONY: run
run:
	$(MAKE) bonus
	 ./$(NAME)

.PHONY: runv
runv:
	$(MAKE) bonus
	valgrind --leak-check=full ./$(NAME)


-include $(DEPS)