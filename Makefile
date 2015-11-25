##
## Makefile for my_ls in /home/boitea_r
## 
## Made by Ronan Boiteau
## Login   <boitea_r@epitech.net>
## 
## Started on  Mon Nov 23 14:30:09 2015 Ronan Boiteau
## Last update Wed Nov 25 19:36:19 2015 Ronan Boiteau
##

NAME	= my_ls

IDIR	= include/

LIB	= libmy.a
LNAME	= my
LDIR	= lib/my

CC	= gcc
CFLAGS	+= -I $(IDIR)
#CFLAGS	+= -Wall -Werror -Wextra -ansi -fstack-protector-all -DNDEBUG

SDIR	= src/
SRCS	= $(SDIR)main.c

OBJS	= $(SRCS:.c=.o)

RM	= rm -f


all: $(LIB) $(NAME)

$(LIB):
	cd $(LDIR) && $(MAKE)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L lib -l $(LNAME)

clean:
	$(RM) $(OBJS)
	cd $(LDIR) && $(MAKE) clean

fclean: clean
	$(RM) $(NAME)
	cd $(LDIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re
