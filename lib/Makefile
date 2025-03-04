# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 14:28:51 by ehosta            #+#    #+#              #
#    Updated: 2025/01/15 14:28:51 by ehosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

include variables.mk

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ) $(HEADERS) $(MAKEFILES)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@echo ""
	@echo "               $(_PURPLE),     \\      /     ,"
	@echo "              / \\     )\\__/(     / \\"
	@echo "             /   \\   (_\\  /_)   /   \\"
	@echo "  $(_BLUE)╔══════════════════ $(_PURPLE)\\@  @$(_PURPLE)/ $(_BLUE)══════════════════╗"
	@echo "  ║                   $(_PURPLE)|\\../|                   $(_BLUE)║"
	@echo "  ║                    $(_PURPLE)\\VV/                    $(_BLUE)║"
	@echo "  ║           $(_PURPLE)私は龍のリブヘフティだ           $(_BLUE)║"
	@echo "  ║             $(_PURPLE)> $(_CYAN)Libft created. $(_PURPLE)<             $(_BLUE)║"
	@echo "  ╚════════════════════════════════════════════╝"
	@echo "        $(_PURPLE)|    /\\ /       \\ \\      \\ /\\    |"
	@echo "        |  /   V        ))        V   \\  |"
	@echo "        |/     \`       //         '     \\|"
	@echo "        \`              V                 '$(_END)"
	@echo ""

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(MAKE_DIR)

.PHONY: fclean
fclean:
	$(RM) $(RMFLAGS) $(NAME) $(MAKE_DIR)

.PHONY : re
re: fclean
	$(MAKE)

.PHONY : norm
norm:
	norminette $(SRC_DIR) include

$(DIRS):
	@mkdir -p $@

-include $(DEPS)