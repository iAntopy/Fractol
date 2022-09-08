#SRCS	= $(wildcard *.c)
SRCS	:= $(filter-out $(wildcard *test.c), $(wildcard *.c))

OBJS	= $(SRCS:.c=.o)

INCLS	= includes/

#LIB_DIR	= ../libs/
#LIBS	= ../libs/libmlx.a ../libs/libft.a

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -I$(INCLS)# $(LIBS)
#CFLAGS	= -I$(INCLS) -L../ -lmlx -lft 

AR	= ar -rcs

NAME	= libmlxadds.a

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
#	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	$(AR) $(NAME) $(OBJS)

all:	$(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
