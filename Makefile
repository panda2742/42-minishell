# The name of the executable
NAME		:=	minishell
# The directory where the object files will stand
MAKE_DIR	:=	.make/
# The subdirectory where the built objects will be, for example ./make/minishell_develop/
BUILD_DIR	:=	$(MAKE_DIR)$(NAME)_$(shell git branch --show-current)/


# The header files directory
override	INCLUDE_DIR		:=	include/
# The C source code files directory
override	SOURCE_DIR		:=	src/
# The header files of the project
override	HEADER_FILES	:=	minishell


# The C source code files of the project
override	SRC_BUILTINS	:=	$(addprefix builtin_,cd echo env exit export pwd unset)
override	SRC_ENV_MANAGER	:=	create_env default_env env_to_strlst get_var
override	SRC_ERRORS		:=	puterr
override	SRC_EXEC		:=	$(addprefix heredoc/, heredoc) \
								$(addprefix init/, create_cmd_utils create_cmd create_execvars create_redirect redirect_manager) \
								$(addprefix process/, exec_multiple_commands exec_single_builtin exec_utils exec execute_from_path)
override	SRC_MEMORY		:=	free_cmds free_env
override	SRC_MISC		:=	print_cmds show_prompt signals build_themes get_random_chars
override	SRC_PARSING		:=	$(addprefix cmd/, cmd) \
								$(addprefix lexer/, handle_redir_pipe lexer_parse lexer_quotes lexer_utils lexer) \
								$(addprefix tokenizer/, expand_caller_utils expand_tokens_utils expand expand_tokens fragments token_lexer token_list_utils token_list_utils2 token_list word_split_token_utils) 
override	SRC_UTILS		:=	$(addprefix parsing/, count_arg_words free_str_return_null ft_add_char ft_split_parser ft_str_join_free ft_strcmp get_first_word handle_is_redir_token incr_on_alnum is_redir join_token_to_string print_t_token_list skip_spaces token_lstsize) \
								$(addprefix main_utils/, create_env exit_if_line_null status_err) \
								empty_tab \
								ft_sprintf \
								int_size
override	SOURCE_FILES	:=	$(addprefix builtins/, $(SRC_BUILTINS)) \
								$(addprefix env_manager/, $(SRC_ENV_MANAGER)) \
								$(addprefix errors/, $(SRC_ERRORS)) \
								$(addprefix exec/, $(SRC_EXEC)) \
								$(addprefix memory/, $(SRC_MEMORY)) \
								$(addprefix misc/, $(SRC_MISC)) \
								$(addprefix parsing/, $(SRC_PARSING)) \
								$(addprefix test/, $(SRC_TEST)) \
								$(addprefix utils/, $(SRC_UTILS)) \
								main


# The libft submodule directory
override	LIBFT_DIR	:=	lib/
# The libft executable path
override	LIBFT		:=	$(LIBFT_DIR)libft.a


# The formatted version of the headers (with directory and extension), for example include/minishell.h
override	HEADER		:=	$(addprefix $(INCLUDE_DIR), $(addsuffix .h, $(HEADER_FILES)))
# The formatted version of the C source code files (with directory and extension), for example src/main.c
override	SOURCE		:=	$(addprefix $(SOURCE_DIR), $(addsuffix .c, $(SOURCE_FILES)))
# Every object for each C source code file
override	OBJ			:=	$(patsubst $(SOURCE_DIR)%.c, $(BUILD_DIR)%.o, $(SOURCE))
# Every dep file (.d) for each C source code file
override	DEPS		:=	$(patsubst %.o,%.d,$(OBJ))
# All the required directories for the build of the project
override	DIRS		:=	$(sort $(dir $(NAME) $(OBJ) $(LIBFT) $(DEPS)))


# The C compilation flags
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP -g3 -D PROJECT_NAME=\"$(NAME)\"
# The Makefile flags to hide the current directory on compilation
MAKEFLAGS	:=	--no-print-directory
# The compiler binary 
GCC			:=	cc
# The rm command used to remove some things
RM			:=	rm -r


.PHONY: all
all: $(NAME)


$(NAME): $(OBJ) $(LIBFT) 
	$(GCC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline


$(BUILD_DIR)%.o: $(SOURCE_DIR)%.c Makefile $(HEADER) | $(DIRS)
	$(GCC) $(CFLAGS) -c -I$(LIBFT_DIR)/include -I$(INCLUDE_DIR) $< -o $@


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
	@norminette $(SOURCE_DIR) $(INCLUDE_DIR) $(LIBFT_DIR) | grep "Error"


.PHONY: run
run:
	clear
	$(MAKE) bonus
	clear
	@./$(NAME)


.PHONY: ab
ab:
	# git pull
	clear
	$(MAKE) bonus
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-mismatched-frees=yes --track-fds=yes --trace-children=yes --suppressions=.valgrind_suppress.txt ./$(NAME)


.PHONY: eh
eh:
	# git pull
	clear
	$(MAKE) bonus
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-mismatched-frees=yes --track-fds=yes --trace-children=yes --suppressions=/home/ehosta/Documents/42-minishell/.valgrind_suppress.txt ./$(NAME) -t 2


-include $(DEPS)