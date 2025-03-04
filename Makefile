NAME				:=	minishell
MAKE_DIR			:=	.make/

override	HDRS	:=	minishell
override	SRCS	:=	main

override	BUILD_DIR	:=	$(MAKE_DIR)$(NAME)_$(shell git branch --show-current)/
override	HDR_DIR		:=	include/
override	HDR			:=	$(addprefix $(HDR_DIR),$(addsuffix .h,$(HDRS)))
override	SRC_DIR		:=	src/
override	SRC			:=	$(addprefix $(SRC_DIR),$(addsuffix .c,$(SRCS)))
override	LIBFT_DIR	:=	libft/
override	LIBFT		:=	$(LIBFT_DIR)libft.a
override	OBJ			:=	$(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC))
override	DEPS		:=	$(patsubst %.o,%.d,$(OBJ))
override	DIRS		:=	$(sort $(dir $(NAME) $(OBJ) $(LIBFT) $(DEPS)))

CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
MAKEFLAGS	:=	--no-print-directory
GCC			:=	cc
RM			:=	rm -rf

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ) $(HDR) $(LIBFT) Makefile
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

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
	norminette $(SRC_DIR) include/ libft/

.PHONY: run
run:
	$(MAKE) bonus
	./$(NAME)

-include $(DEPS)