NAME=woody_woodpacker
SRC=src/main.c src/libft.c
OBJ = $(SRC:.c=.o)
FLAGS= -g -Wall -Wextra -Werror -Wformat-security -fsanitize=address
INC=inc/woody.h

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(INC)
		gcc $(FLAGS) -c -o $@ $<

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME) woody

re: fclean all

all: $(NAME)

add: test fclean
		git add .gitignore $(SRC) Makefile $(INC) README.md Dockerfile

commit: add
		git commit -m "`uname -n | cut -d. -f1`"

push: commit
		git push origin main

test: re
	./test.sh /bin/bash 