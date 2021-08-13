NAME=woody_woodpacker
SRC=src/main.c
OBJ = $(SRC:.c=.o)
FLAGS= -O2 -Wall -Wextra -Werror -Wformat-security
LIBFT=libft/libft.a
INC=inc/$(NAME).h

$(NAME): $(OBJ) $(LIBFT) 
	gcc $(FLAGS) $(OBJ) -I libft -L libft -lft -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c $(INC)
	gcc $(FLAGS) -c -o $@ $<

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

all: $(NAME)

add:
	git add $(SRC) Makefile $(INC) README.md

commit: add
	git commit -m "`uname -n | cut -d. -f1`"