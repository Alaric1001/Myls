NAME 	= ft_ls
CC		= gcc
FLAGS	= 
LIBPATH	= libft/
SRC		= main.c \
		  core.c \
		  utils.c \
		  display/standard_disp.c \
		  display/advanced_disp.c \
		  stock/stockvisible.c \
		  stock/stockall.c \
		  parsing/params.c
SRCS	= $(addprefix srcs/, $(SRC))
BIN		= $(addprefix bin/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): bindir libft $(BIN)
	@echo "Generating" $(NAME)"..."
	@$(CC) $(FLAGS) $(BIN) -o $(NAME) -L./$(LIBPATH) -lft
	@echo $(NAME) "generation done."

bin/%.o: srcs/%.c includes/ls.h
	@$(CC) -o $@ -c $< $(FLAGS) -I includes
	@echo ">"$@ "generated successfully."

bindir:
	@mkdir -p bin bin/parsing bin/stock bin/display

libft:
	@make -C $(LIBPATH)

clean:
	@rm -rf $(bin)
	@make -c $(LIBPATH) clean
	@echo "All objects files cleaned up !"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBPATH)libft.a
	@echo $(NAME) "and libft.a cleaned up !"

re: fclean all

.PHONY: all bindir libft clean fclean re
