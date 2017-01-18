NAME 	= ft_ls
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
LIBPATH	= libft/
SRC		= main.c \
		  core.c \
		  utils.c \
		  padding.c \
		  freemem.c \
		  display/standard_disp.c \
		  display/advanced_disp.c \
		  display/adv_disputils.c \
		  stock/stockvisible.c \
		  stock/stockall.c \
		  sort/asciisort.c \
		  sort/timesort.c \
		  parsing/params.c
SRCS	= $(addprefix srcs/, $(SRC))
BIN		= $(addprefix bin/, $(SRC:.c=.o))

GREEN	= "\033[32m"
RESET	= "\033[0m"

all: | bindir $(NAME)

$(NAME): libft $(BIN)
	@echo "Generating" $(NAME)"..."
	@$(CC) $(FLAGS) $(BIN) -o $(NAME) -L./$(LIBPATH) -lft
	@echo $(GREEN)$(NAME) "generation done." $(RESET)

bin/%.o: srcs/%.c includes/ls.h
	@$(CC) -o $@ -c $< $(FLAGS) -I includes -I $(LIBPATH)includes
	@echo ">"$@ "generated successfully."

bindir:
	@mkdir -p bin bin/parsing bin/stock bin/display bin/sort

libft:
	@make -C $(LIBPATH)

clean:
	@rm -rf $(BIN)
	@make -C $(LIBPATH) clean
	@echo "All objects files cleaned up !"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBPATH)libft.a
	@echo $(NAME) "and libft.a cleaned up !"

re: fclean all

.PHONY: all bindir libft clean fclean re
