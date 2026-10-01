## valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

#{
#   leak readline
#   Memcheck:Leak
#   ...
#   fun:readline
#}
#{
#   leak add_history
#   Memcheck:Leak
#   ...
#   fun:add_history
#}

CC = gcc -g3 -Wall -Wextra -Werror -MMD # -fsanitize=thread

SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep

SRC_EXT = .c
OBJ_EXT = .o
DEP_EXT = .d


SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/main_utils.c \
		$(SRC_DIR)/ft_itoa.c \
		$(SRC_DIR)/ft_split.c \
		$(SRC_DIR)/signals.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/parsing_utils.c \
		$(SRC_DIR)/parse_heredoc.c \
		$(SRC_DIR)/tree.c \
		$(SRC_DIR)/tree_utils.c \
		$(SRC_DIR)/actions.c \
		$(SRC_DIR)/all_star.c \
		$(SRC_DIR)/exec_utils.c \
		$(SRC_DIR)/env_utils.c	\
		$(SRC_DIR)/builtins/builtins.c \
		$(SRC_DIR)/builtins/cd.c \
		$(SRC_DIR)/builtins/echo.c \
		$(SRC_DIR)/builtins/env.c \
		$(SRC_DIR)/builtins/exit.c \
		$(SRC_DIR)/builtins/export.c \
		$(SRC_DIR)/builtins/pwd.c \
		$(SRC_DIR)/builtins/unset.c \
		$(SRC_DIR)/syntax.c \
		$(SRC_DIR)/env_func.c \
		$(SRC_DIR)/expansion.c \
		$(SRC_DIR)/handles/handle_cmd.c \
		$(SRC_DIR)/handles/handle_pipe.c \
		$(SRC_DIR)/handles/handle_orand.c \
		$(SRC_DIR)/handles/handle_less.c \
		$(SRC_DIR)/handles/handle_word.c \
		$(SRC_DIR)/utils.c


OBJS = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:$(SRC_EXT)=$(OBJ_EXT)))


DEPS = $(patsubst $(SRC_DIR)/%,$(DEP_DIR)/%,$(SRCS:$(SRC_EXT)=$(DEP_EXT)))

SRCH_INCLDS = -Iincludes

RM = rm -rf
MKDIR = mkdir -p

RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m

NAME = minishell

all: $(NAME)

-include $(DEPS)

$(OBJ_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%$(SRC_EXT)
	@$(MKDIR) $(@D)
	@echo "$(GREEN)Compiling$(RESET) $<..."
	@$(CC) $(SRCH_INCLDS) -c $< -o $@


$(DEP_DIR)/%$(DEP_EXT): $(SRC_DIR)/%$(SRC_EXT)
	@$(MKDIR) $(@D)
	@echo "$(GREEN)Generating dependencies$(RESET) for $<..."
	@$(CC) $(SRCH_INCLDS) -MM -MT '$(OBJ_DIR)/$*$(OBJ_EXT)' $< -MF $@

$(NAME): $(OBJS)
	@echo "$(BOLD)Linking$(RESET) $(NAME)..."
	@$(CC) $(OBJS) -lreadline -o $(NAME)
	@echo "$(BOLD)$(GREEN)$(NAME) has been compiled successfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning$(RESET) object files..."
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)Cleaning$(RESET) dependencies..."
	@$(RM) $(DEP_DIR)

fclean: clean
	@echo "$(RED)Cleaning$(RESET) $(NAME)..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
