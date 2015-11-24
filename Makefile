##
## Makefile for my_ls in /home/boitea_r
## 
## Made by Ronan Boiteau
## Login   <boitea_r@epitech.net>
## 
## Started on  Mon Nov 23 14:30:09 2015 Ronan Boiteau
## Last update Tue Nov 24 21:43:19 2015 Ronan Boiteau
##

NAME	= my_ls

IDIR	= include/

LIB	= libmy.a
LNAME	= my
LDIR	= lib/my

CC	= gcc
CFLAGS	+= -I $(IDIR)
#CFLAGS	+= -Wall -Werror -Wextra -ansi

SDIR	= src/
SRCS	= $(SDIR)list.c				\
	  $(SDIR)main.c

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