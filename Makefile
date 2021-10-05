NAME=woody_woodpacker
SRC=src/main.c src/libft.c
OBJ = $(SRC:.c=.o)
FLAGS= -Wall -Wextra -Werror -g -Wformat-security
INC=inc/woody.h
ASMSRC=asm/woody.s asm/get_opcode.sh

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

test: re x h fclean

x: $(NAME)
	./woody_woodpacker woody_woodpacker
	ls -la woody
	./woody | true
xx: x
	binwalk -W woody $(NAME) | less

h: $(NAME) test/hello.c
	gcc -O3 test/hello.c -o test/hello
	./$(NAME) test/hello
	echo
	./woody | true

e: $(NAME)
	./$(NAME) /bin/echo
	echo
	./woody | true
ee: e
	binwalk -W woody /bin/echo
hh: h
	binwalk -W test/hello woody | less
diff: $(NAME)
	rm -f woody
	./$(NAME) $(NAME)
	binwalk -W woody $(NAME) |less

.PHONY: test re all