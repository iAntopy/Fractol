SRCS	= $(wildcard *.c)

OBJS	= $(SRCS:.c=.o)

INCLS	= includes/
LIBS	= ../libmlx.a ../libft.a

CC	= gcc
#CFLAGS	= -Wall -Wextra -Werror -I$(INCLS) -L../ -lmlx -lft 
#CFLAGS	= -I$(INCLS) -L../ -lmlx -lft 
CFLAGS	= -I$(INCLS)

AR	= ar -rcs

NAME	= libmlxadds.a

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(LIBS)

$(NAME):	$(OBJS)
#	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	$(AR) $(NAME) $(OBJS)

all:	$(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
