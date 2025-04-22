 



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
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✨ Cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(GREEN)✨ Everything cleaned!$(RESET)"

norm:
	@echo "$(BLUE)Running norminette check...$(RESET)"
	@echo "$(YELLOW)Checking source files:$(RESET)"
	@python3 -m c_formatter_42 $(ROOT_DIR)/*.c $(EXEC_DIR)/*.c $(BUILTINS_DIR)/*.c $(UTILS_DIR)/*.c \
	    $(LEXER_DIR)/*.c $(DATA_DIR)/*.c $(READLINE_DIR)/*.c $(PARSER_DIR)/*.c
	@echo "$(YELLOW)Checking header files:$(RESET)"
	@python3 -m c_formatter_42 $(INCLUDE_DIR)/*.h
	@echo "$(GREEN)✨ Norminette check complete!$(RESET)"

push:
	@git add .
	@echo -n "$(BLUE)Enter your commit message: $(END)"
	@read commit_message; \
	git commit -m "$$commit_message"; \
	git push; \
	echo "$(YELLOW)All has been pushed with '$$commit_message' in commit$(END)"

.PHONY: clean fclean norm push