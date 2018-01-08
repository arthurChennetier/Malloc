##
## Makefile for Makefile in /home/chenne_a/rendu/tech2/PSU_2016_malloc
## 
## Made by chennetier
## Login   <arthur.chennetier@epitech.eu>
## 
## Started on  Wed Jan 25 11:03:45 2017 chennetier
## Last update Sun Feb 12 22:27:10 2017 chennetier
##

SRC	=	malloc.c \
		free.c \
		realloc.c \
		new_space.c \
		new_space2.c \
		show_mem.c

CC	=	gcc

NAME	=	libmy_malloc.so

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Werror -Wextra -g3

RM	=	rm -f

all: 	$(NAME)

$(NAME): $(OBJ)
	$(CC) -c $(CFLAGS) -fpic $(SRC) -lpthread
	$(CC) -shared -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all
