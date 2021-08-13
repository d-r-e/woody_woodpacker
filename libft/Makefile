# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darodrig <darodrig@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 14:36:20 by darodrig          #+#    #+#              #
#    Updated: 2019/11/14 12:16:34 by darodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ar rcs
RM = rm -f

CC = gcc

CCFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c \
	  ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  ft_toupper.c ft_tolower.c ft_strdup.c ft_strcpy.c ft_strlcat.c ft_atoi.c \
	  ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strrchr.c ft_strnstr.c ft_memccpy.c \
	  ft_memmove.c ft_strlcpy.c ft_isspace.c ft_calloc.c ft_strchr.c\
	  ft_substr.c ft_strjoin.c ft_strtrim.c ft_strncpy.c ft_strcmp.c ft_charcount.c \
	  ft_wordlen.c ft_wordcount.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
	  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJ = $(SRC:.c=.o)

INCLUDE = libft.h

BONUSSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		   ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		   ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUSOBJ = $(BONUSSRC:.c=.o) 

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(LIB) $(NAME) $(OBJ)

bonus: $(BONUSOBJ) $(INCLUDE)
	$(LIB) $(NAME) $(BONUSOBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJ) $(BONUSOBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus


.PHONY: clean fclean
