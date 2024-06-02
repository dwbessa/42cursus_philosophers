NAME		= philo
SRC			= $(shell find src -name '*.c')
OBJ			= ${patsubst src/%.c, objs/%.o, $(SRC)}
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
INCLUDE		= -I includes/
RM			= rm -rf
SILENT		= @
COLOR_RESET	= \033[0m
COLOR_GREEN	= \033[32m
COLOR_YELLOW	= \033[33m
COLOR_RED	= \033[31m
BLINK		= \033[5m

all: $(NAME)

objs:
	@mkdir -p objs

$(OBJ): objs/%.o: src/%.c | objs
	@mkdir -p $(dir $@)
	$(SILENT) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ 2>/dev/null

$(NAME): $(OBJ)
	$(SILENT) $(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME) 2>/dev/null
	@echo "✅ $(BLINK)$(COLOR_GREEN)Philosophers is ready!$(COLOR_RESET)"

clean:
	$(SILENT) ${RM} ${OBJ}
	@rm -rf objs
	@echo "👀 $(COLOR_YELLOW)Cleaned up object files$(COLOR_RESET)"

fclean: clean
	$(SILENT) ${RM} $(NAME)
	@echo "🔥 $(COLOR_RED)Removed $(NAME) executable$(COLOR_RESET)"

re: fclean all

.PHONY: all clean fclean re
