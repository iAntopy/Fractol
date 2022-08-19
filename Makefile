#SRCS	= $(wildcard *.c)

#SRCS	:= $(filter-out $(wildcard src/*pool.c), $(wildcard src/*.c))
SRCS	:= $(wildcard src/*.c) $(wildcard src/dist_funcs/*.c)

OBJS	= $(SRCS:.c=.o)

INCLS	= includes/

LIBS_DIR	= libs/
LIBS		=  $(LIBS_DIR)libft.a $(LIBS_DIR)libmlxadds.a $(LIBS_DIR)libmlx.a

CC		= gcc

CFLAGS		= -Wall -Wextra -Werror -O2

ifeq ($(shell uname -s), Linux)
	FRAMEWORKS	= -lm -lX11 -lXext
endif
ifeq ($(shell uname -s), Darwin)
	FRAMEWORKS	= -framework OpenGL -framework Appkit
endif
#CFLAGS		= -I$(INCLS) -L../ -lmlx -lft 

NAME	= Fractol

.c.o:
	$(CC) $(CFLAGS) -I$(INCLS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(FRAMEWORKS) $(OBJS) -o $(NAME) $(LIBS) 

all:	$(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
