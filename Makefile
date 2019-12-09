NAME	= my_ls

IDIR	= include/
IDIR_MY	= lib/my/include/

LIB	= libmy.a
LNAME	= my
LDIR	= lib/my

CC	= gcc
CFLAGS	+= -I $(IDIR) -I $(IDIR_MY)
CFLAGS	+= -Wall -Werror -Wextra

SRCS_DIR	= src/
SRCS_FILES	= main.c			\
		  handle_args.c			\
		  handle_options.c		\
		  option_a.c			\
		  option_none.c			\
		  option_r.c			\
		  paths_count.c			\
		  paths.c
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS	= $(SRCS:.c=.o)

RM	= rm -f


all: $(LIB) $(NAME)

$(LIB):
	make -C $(LDIR)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L $(LDIR) -l $(LNAME)

clean:
	$(RM) $(OBJS)
	make -C $(LDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LDIR) fclean

re: fclean all

.PHONY: all clean fclean re
