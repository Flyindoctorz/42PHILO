# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 17:00:14 by cgelgon           #+#    #+#              #
#    Updated: 2025/04/25 16:27:01 by cgelgon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I.
LDFLAGS = -pthread

SRC_DIR = .

SRC_FILES = 	philo_utils.c \
				parse_args.c \
				philo_routine.c \
				init_all.c \
				checker.c \
				cleaner.c \
				main_utils.c \
				routine_core.c \
				main.c 
			
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

all : $(NAME)

$(OBJ_DIR) :
	@mkdir -p $@
	
$(NAME) : $(OBJ_DIR) $(OBJS)
	@echo "$(BLUE)Compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)
	@echo "$(BLUE)✨ Compilation complete!$(RESET)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Colors
BLUE = \033[0;34m
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m
BOLD = \033[1m

# Règles de nettoyage
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJS)
	@echo "$(GREEN)✨ Cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✨ Everything cleaned!$(RESET)"

re : fclean all

norm:
	@echo "$(BLUE)Running norminette check...$(RESET)"
	@echo "$(YELLOW)Checking source files:$(RESET)"
	@python3 -m c_formatter_42 $(SRCS)
	@echo "$(YELLOW)Checking header files:$(RESET)"
	@python3 -m c_formatter_42 philo.h || true
	@echo "$(GREEN)✨ Norminette check complete!$(RESET)"

# Helgrind it (USAGE : make dataraces ARGS=" AV1 AV2 AV3 AV4")	
dataraces:
	@echo "$(BLUE)Running Helgrind data race detector...$(RESET)"
	@echo "$(YELLOW)Input args: $(ARGS)$(RESET)"
	@valgrind --tool=helgrind ./$(NAME) $(ARGS)
	@echo "$(GREEN)Helgrind analysis complete!$(RESET)"

push:
	@git add .
	@echo -n "$(BLUE)Enter your commit message: $(END)"
	@read commit_message; \
	git commit -m "$$commit_message"; \
	git push; \
	echo "$(YELLOW)All has been pushed with '$$commit_message' in commit$(END)"

debug:
	@echo "$(BLUE)Running lldb...$(RESET)"
	@lldb ./$(NAME)

.PHONY: clean fclean norm push re debug all norm dataraces 