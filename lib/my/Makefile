##
## Makefile for libmy in /home/boitea_r
## 
## Made by Ronan Boiteau
## Login   <boitea_r@epitech.net>
## 
## Started on  Tue Nov 10 15:47:58 2015 Ronan Boiteau
## Last update Wed Nov 25 19:34:17 2015 Ronan Boiteau
##

IDIR	= include/
INC	= $(IDIR)my.h					\
	  $(IDIR)my_macro.h				\
	  $(IDIR)string.h				\
	  $(IDIR)variadic.h

CC	= gcc
CFLAGS	+= -I $(IDIR)
CFLAGS	+= -Wall -Werror -Wextra -ansi

RM	= rm -f

NAME	= libmy.a

SDIR	= src/
SRCS	= $(SDIR)match.c				\
	  $(SDIR)my_char_is/my_char_isalpha.c		\
	  $(SDIR)my_char_is/my_char_islower.c		\
	  $(SDIR)my_char_is/my_char_isnum.c		\
	  $(SDIR)my_char_is/my_char_isprintable.c	\
	  $(SDIR)my_char_is/my_char_isupper.c		\
	  $(SDIR)my_exit.c				\
	  $(SDIR)my_find_prime_sup.c			\
	  $(SDIR)my_getnbr.c				\
	  $(SDIR)my_is_prime.c				\
	  $(SDIR)my_isneg.c				\
	  $(SDIR)my_max_int_tab.c			\
	  $(SDIR)my_min_int_tab.c			\
	  $(SDIR)my_puts/my_put_error.c			\
	  $(SDIR)my_puts/my_put_nbr.c			\
	  $(SDIR)my_puts/my_putchar.c			\
	  $(SDIR)my_puts/my_putnbr_base.c		\
	  $(SDIR)my_puts/my_putstr.c			\
	  $(SDIR)my_power.c				\
	  $(SDIR)my_revstr.c				\
	  $(SDIR)my_showstr.c				\
	  $(SDIR)my_sort_int_tab.c			\
	  $(SDIR)my_square_root.c			\
	  $(SDIR)my_str_is/my_str_isalpha.c		\
	  $(SDIR)my_str_is/my_str_islower.c		\
	  $(SDIR)my_str_is/my_str_isnum.c		\
	  $(SDIR)my_str_is/my_str_isprintable.c		\
	  $(SDIR)my_str_is/my_str_isupper.c		\
	  $(SDIR)my_strcapitalize.c			\
	  $(SDIR)my_strcmp.c				\
	  $(SDIR)my_strdup.c				\
	  $(SDIR)my_strlen.c				\
	  $(SDIR)my_strlowcase.c			\
	  $(SDIR)my_strncat.c				\
	  $(SDIR)my_strncmp.c				\
	  $(SDIR)my_strncpy.c				\
	  $(SDIR)my_strstr.c				\
	  $(SDIR)my_strupcase.c				\
	  $(SDIR)my_swap.c				\
	  $(SDIR)nmatch.c

OBJS	= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)
	cp $(NAME) ..
	cp $(INC) ../../$(IDIR)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
