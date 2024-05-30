NAME		= philo
SRC			= $(shell find src -name '*.c')
OBJ			= ${patsubst src/%.c, objs/%.o, $(SRC)}
CC			= cc
CFLAGS	= -Wall -Werror -Wextra -g
INCLUDE	= -I includes/
RM			= rm -rf

all: $(NAME)

objs:
			@mkdir -p objs

$(OBJ): objs/%.o: src/%.c | objs
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
				$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME)

clean:
				${RM} ${OBJ}
				@rm -rf objs

fclean: clean
				${RM} $(NAME)

re: fclean all

.PHONY:		all clean fclean re
