
COM_DIR		= ./
MAN_DIR		= mandatory/
BNS_DIR		= bonus/

SRC_COM		= $(wildcard $(COM_DIR)src/*.c) $(wildcard $(COM_DIR)src/dist_funcs/*.c)
SRC_M		= $(wildcard $(MAN_DIR)src/*.c)# $(wildcard $(MAN_DIR)src/dist_funcs/*.c)
SRC_B		= $(wildcard $(BNS_DIR)src/*.c)# $(wildcard $(BNS_DIR)src/dist_funcs/*.c)

OBJ_COM		= $(SRC_COM:.c=.o)
OBJ_M		= $(SRC_M:.c=.mo)
OBJ_B		= $(SRC_B:.c=.bo)

BASE_INCL	= includes/
MAN_INCL	= $(MAN_DIR)includes/
BNS_INCL	= $(BNS_DIR)includes/

LIBS_DIR	= libs/
LIBS		= $(wildcard $(LIBS_DIR)*.a)

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O2

NAME		= Fractol
NAME_BONUS	= Fractol_bonus

ifeq ($(shell uname -s), Linux)
	MLX_DIR		= $(LIBS_DIR)minilibx/minilibx-linux/
	FRAMEWORKS	= -lm -lX11 -lXext
endif
ifeq ($(shell uname -s), Darwin)
	MLX_DIR		= $(LIBS_DIR)minilibx/minilibx_macos/
	FRAMEWORKS	= -framework OpenGL -framework Appkit
endif

%.o:	%.c
	$(CC) $(CFLAGS) -I$(BASE_INCL) -c $< -o $@
%.mo:	%.c
	$(CC) $(CFLAGS) -I$(BASE_INCL) -I$(MAN_INCL) -c $< -o $@
%.bo:	%.c
	$(CC) $(CFLAGS) -I$(BASE_INCL) -I$(BNS_INCL) -c $< -o $@

all:	$(NAME)

$(NAME):	build_libs $(OBJ_COM) $(OBJ_M)
	$(CC) $(CFLAGS) $(FRAMEWORKS) $(OBJ_COM) $(OBJ_M) -o $(NAME) $(LIBS)

$(NAME_BONUS):	build_libs $(OBJ_COM) $(OBJ_B)
	$(CC) $(CFLAGS) $(FRAMEWORKS) $(OBJ_COM) $(OBJ_B) -o $(NAME_BONUS) $(LIBS)

bonus:	$(NAME_BONUS)

clean: clean_commons clean_mandatory clean_bonus
	make -C $(LIBS_DIR)libft clean
	make -C $(LIBS_DIR)mlx_addons clean
	make -C $(MLX_DIR) clean

clean_commons:
	rm -f $(OBJ_COM)
clean_mandatory:
	rm -f $(OBJ_M)
clean_bonus:
	rm -f $(OBJ_B)
clean_man:	clean_mandatory

fclean:	clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	rm -f $(LIBS)

build_libs:
	@echo "Building libs ..."
	make -C $(LIBS_DIR)libft
	cp $(LIBS_DIR)libft/libft.a $(LIBS_DIR)
	make -C $(LIBS_DIR)mlx_addons
	cp $(LIBS_DIR)mlx_addons/libmlxadds.a $(LIBS_DIR)
	make -C $(MLX_DIR)
	cp $(MLX_DIR)libmlx.a $(LIBS_DIR)

re:	fclean all

.PHONY:	all re clean fclean clean_bonus clean_commons clean_mandatory bonus 
