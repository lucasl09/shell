# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 16:34:27 by roglopes          #+#    #+#              #
#    Updated: 2024/06/29 15:41:18 by roglopes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME                = minishell

SOURCES_DIR         = sources/
OBJECTS_DIR         = objects/

HEADERS             = -I ./includes/mandatory/ -I ./libft/include/

MAIN_DIR            = $(SOURCES_DIR)mandatory/main/
PROMPT_DIR          = $(SOURCES_DIR)mandatory/prompt/
TOKEN_DIR           = $(SOURCES_DIR)mandatory/tokenizer/
EXPANSION_DIR       = $(SOURCES_DIR)mandatory/expansion/
COMMAND_DIR         = $(SOURCES_DIR)mandatory/command/
BUILTINS_DIR        = $(SOURCES_DIR)mandatory/builtins/
UTILS_DIR           = $(SOURCES_DIR)mandatory/utils/
FREE_DIR            = $(SOURCES_DIR)mandatory/free/
INIT_DIR            = $(SOURCES_DIR)mandatory/initialize/

LIBFT               = ./libft/libft.a

CFLAGS              = -Wextra -Wall -Werror -g3
CC                  = cc

VALGRIND_LOG        = valgrind.log

MAIN_SOURCES        = $(MAIN_DIR)main.c

PROMPT_SOURCES      = $(PROMPT_DIR)prompt.c                \
                    $(PROMPT_DIR)signal.c

TOKEN_SOURCES       = $(TOKEN_DIR)tokenizer.c              \
                    $(TOKEN_DIR)create_token.c

EXPANSION_SOURCES   = $(EXPANSION_DIR)variable_expansion.c \
                    $(EXPANSION_DIR)variable_expansion2.c

COMMAND_SOURCES     = $(COMMAND_DIR)execute_command.c      \
                    $(COMMAND_DIR)execute_command2.c

BUILTINS_SOURCES    = $(BUILTINS_DIR)builtins.c            \
                    $(BUILTINS_DIR)builtins2.c

UTILS_SOURCES       = $(UTILS_DIR)utils.c                  \
                    $(UTILS_DIR)utils2.c                   \
                    $(UTILS_DIR)utils3.c

FREE_SOURCES        = $(FREE_DIR)free_type.c

INITIALIZE_SOURCES  = $(INIT_DIR)init_check.c              \
                    $(INIT_DIR)init_hp.c                  \
                    $(INIT_DIR)init_redirect.c            \
                    $(INIT_DIR)init_tree.c

SOURCES             = $(MAIN_SOURCES) $(UTILS_SOURCES)     \
                    $(TOKEN_SOURCES) $(FREE_SOURCES)       \
                    $(PROMPT_SOURCES) $(COMMAND_SOURCES)   \
                    $(INITIALIZE_SOURCES) $(EXPANSION_SOURCES) \
                    $(BUILTINS_SOURCES)

OBJS                = $(patsubst $(SOURCES_DIR)%.c,$(OBJECTS_DIR)%.o, $(SOURCES))

COUNT               := 0
RED                 = \033[0;31m
GREEN               = \033[0;32m
MAGENTA             = \033[0;35m
RESET               = \033[0m
CYAN                = \033[36;1;3;208m
YELLOW              = \033[0;33m
COLOR_LIMITER       = "\033[0m"

all: create_objects_dir libft $(OBJECTS_DIR) $(NAME)

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(@D)
	@$(eval COUNT=$(shell expr $(COUNT) + 1))
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@printf "$(GREEN)Compiling Mini Shell %d%%\r$(RESET)" $$(echo $$(($(COUNT) * 100 / $(words $(SOURCES)))))

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME) -lreadline

create_objects_dir:
	@mkdir -p $(OBJECTS_DIR)

libft:
	@make -C ./libft --no-print-directory

clean:
	@make clean -C ./libft --no-print-directory
	@rm -rf $(OBJECTS_DIR)
	@rm -rf $(VALGRIND_LOG)
	@printf "$(RED)Deleted objects Mini Shell$(RESET)\n"

fclean: clean
	@echo "Cleaning all... 🧹"
	@rm -rf $(NAME)
	@make fclean -C ./libft --no-print-directory
	@printf "$(RED)Project is deleted Mini Shell$(RESET)\n"
	@printf "$(RED)File valgrind.log deleted$(RESET)\n"
	@echo "✨ Cleaning complete! ✨"

norm:
	@norminette -R CheckForbiddenSource
	@echo "$(CYAN)NORMINETTE OK $(RESET)"

valgrind: all
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--suppressions=readline.supp \
	--log-file=$(VALGRIND_LOG) \
	./$(NAME)
	@cat $(VALGRIND_LOG)

re: fclean all
	@echo "$(BLUE) $(NAME) Cleaned and rebuilt everything!"

.PHONY: all clean fclean re libft bonus norm create_objects_dir valgrind
