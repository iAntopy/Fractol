#SRCS	= $(wildcard *.c)

SRCS	:= $(filter-out $(wildcard src/*pool.c), $(wildcard src/*.c))

OBJS	= $(SRCS:.c=.o)

INCLS	= includes/

LIBS_DIR	= libs/
LIBS		=  $(LIBS_DIR)libft.a $(LIBS_DIR)libmlxadds.a $(LIBS_DIR)libmlx.a

CC		= gcc

ifeq ($(shell uname -s), Linux)
	CFLAGS		= -Wall -Wextra -Werror -lm -lX11 -lXext -O2 -I$(INCLS) -L$(LIBS_DIR)
endif
ifeq ($(shell uname -s), Darwin)
	CFLAGS		= -Wall -Wextra -Werror -lm -framework OpenGL -framework Appkit -O2 -I$(INCLS) -L$(LIBS_DIR)
endif
#CFLAGS		= -I$(INCLS) -L../ -lmlx -lft 

NAME	= Fractol

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

all:	$(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
