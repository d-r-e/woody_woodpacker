NAME=woody_woodpacker
SRC=src/main.c src/string.c src/elf.c src/injection.c src/random.c
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
	rm -f $(NAME) woody

re: fclean all

all: $(NAME)

add: test fclean
	git add .gitignore $(SRC) Makefile $(INC) README.md Dockerfile

commit: add
	git commit -m "`uname -n | cut -d. -f1`"

push: commit
	git push origin main

test: $(NAME)
	./$(NAME) $(NAME)

x: $(NAME)
	@rm -f woody
	./woody_woodpacker resources/sample2
s: $(NAME)
	@rm -f woody
	./woody_woodpacker woody_woodpacker

diff: s
	binwalk -W woody_woodpacker woody -o 0x3250 | less

norm:
	norminette src/*.c