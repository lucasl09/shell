# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 16:34:27 by roglopes          #+#    #+#              #
#    Updated: 2024/07/13 18:22:56 by roglopes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell

SOURCES_DIR			= sources/
OBJECTS_DIR			= objects/

HEADERS				= -I ./includes/mandatory/ -I ./libft/include/

MAIN_DIR			= $(SOURCES_DIR)mandatory/main/
PROMPT_DIR			= $(SOURCES_DIR)mandatory/prompt/
INITIALIZE_DIR		= $(SOURCES_DIR)mandatory/initialize/
TOKEN_DIR			= $(SOURCES_DIR)mandatory/tokenizer/
EXPANSION_DIR		= $(SOURCES_DIR)mandatory/expansion/
COMMAND_DIR			= $(SOURCES_DIR)mandatory/command/
BUILTINS_DIR		= $(SOURCES_DIR)mandatory/builtins/
UTILS_DIR			= $(SOURCES_DIR)mandatory/utils/
FREE_DIR			= $(SOURCES_DIR)mandatory/free/

LIBFT				= ./libft/libft.a

CFLAGS				= -Wextra -Wall -Werror -g3
CC					= cc

VALGRIND_LOG		= valgrind.log

MAIN_SOURCES		= $(MAIN_DIR)main.c             

PROMPT_SOURCES		= $(PROMPT_DIR)prompt.c                \
					$(PROMPT_DIR)signal.c

INITIALIZE_SOURCES	= $(INITIALIZE_DIR)init_check.c \
					$(INITIALIZE_DIR)init_heredoc.c \
					$(INITIALIZE_DIR)init_redirect.c \
					$(INITIALIZE_DIR)init_pipe.c \

TOKEN_SOURCES		= $(TOKEN_DIR)tokenizer.c              \
					$(TOKEN_DIR)justify_type_tokens.c      \
					$(TOKEN_DIR)manage_tokens.c            \
					$(TOKEN_DIR)org_tokens.c               \
					$(TOKEN_DIR)create_token.c             \

EXPANSION_SOURCES	= $(EXPANSION_DIR)variable_expansion.c \
					$(EXPANSION_DIR)variable_expansion2.c

COMMAND_SOURCES		= $(COMMAND_DIR)execute_command.c      \
					$(COMMAND_DIR)execute_command2.c       \
					$(COMMAND_DIR)execute_command3.c       \
					$(COMMAND_DIR)execute_command4.c       \
					$(COMMAND_DIR)execute_command5.c       \
					$(COMMAND_DIR)execute_command6.c       \

BUILTINS_SOURCES	= $(BUILTINS_DIR)builtins.c            \
					$(BUILTINS_DIR)builtins2.c             \
					$(BUILTINS_DIR)builtins3.c             \
					$(BUILTINS_DIR)builtins4.c             \

UTILS_SOURCES		= $(UTILS_DIR)utils1.c                 \
					$(UTILS_DIR)utils2.c                   \
					$(UTILS_DIR)utils3.c				   \
					$(UTILS_DIR)utils4.c                   \
					$(UTILS_DIR)utils5.c                   \
					$(UTILS_DIR)utils6.c                   \
					$(UTILS_DIR)utils7.c                   \
					$(UTILS_DIR)utils8.c                   \
					$(UTILS_DIR)utils9.c                   \
					$(UTILS_DIR)utils10.c                  \
					$(UTILS_DIR)utils11.c                  \
					$(UTILS_DIR)utils12.c                  \
					$(UTILS_DIR)utils13.c                  \
					$(UTILS_DIR)utils14.c                  \

FREE_SOURCES		= $(FREE_DIR)free_type.c

SOURCES				= $(MAIN_SOURCES) $(PROMPT_SOURCES) \
					$(FREE_SOURCES) $(INITIALIZE_SOURCES) \
					$(TOKEN_SOURCES) $(UTILS_SOURCES) \
					$(BUILTINS_SOURCES) $(COMMAND_SOURCES) \
					$(EXPANSION_SOURCES) \

OBJS				= $(patsubst $(SOURCES_DIR)%.c,$(OBJECTS_DIR)%.o, $(SOURCES))

COUNT				:= 0
RED					= \033[0;31m
GREEN				= \033[0;32m
MAGENTA				= \033[0;35m
RESET				= \033[0m
CYAN				= \033[36;1;3;208m
YELLOW				= \033[0;33m
COLOR_LIMITER		= "\033[0m"

all: create_objects_dir libft $(OBJECTS_DIR) $(NAME)

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(@D)
	@$(eval COUNT=$(shell expr $(COUNT) + 1))
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@printf "$(GREEN)Compiling Mini Hell %d%%\r$(RESET)" $$(echo $$(($(COUNT) * 100 / $(words $(SOURCES_DIR)))))

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
	@echo "$(CYAN)NORMINETTE SUCESS $(RESET)"

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
