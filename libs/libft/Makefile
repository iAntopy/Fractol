FUNC_NAMES_M = ft_issign ft_isspace ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove ft_strlcpy ft_strlcat ft_isupper ft_islower ft_toupper ft_tolower ft_strchr ft_strrchr ft_strcmp ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi ft_calloc ft_strlcat ft_substr ft_strjoin ft_strtrim ft_split ft_split_set ft_split_space ft_itoa ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_strdup ft_pow ft_strlower ft_strupper ft_printf ft_vprintf ft_random ft_clamp ft_deltatime_usec ft_memclear fperror

FUNC_NAMES_B = lstnew lstcreate lstinsert lstadd_front lstadd_back lstsize lstlast lstdelone lstclear lstiter lstmap lstpop lstmap lstprint

PREF		= ft_
SUF_M		= .c

#SRCS_TEMP_M	= ${addprefix ${PREF}, ${FUNC_NAMES_M}}
SRCS_M		= ${addsuffix ${SUF_M}, ${FUNC_NAMES_M}}#${SRCS_TEMP_M}}

SRCS_TEMP_B	= ${addprefix ${PREF}, ${FUNC_NAMES_B}}
SRCS_B		= ${addsuffix ${SUF_M}, ${SRCS_TEMP_B}}

SRCS_X		= ${addsuffix ${SUF_M}, ${FUNC_NAMES_EXTRA}}

OBJS_M		= ${SRCS_M:.c=.o}
OBJS_B		= ${SRCS_B:.c=.o}
OBJS_X		= ${SRCS_X:.c=.o}

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

AR			= ar -rcs

RM			= rm -f

NAME		= libft.a

.c.o:
			-${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS_M}
			${AR} ${NAME} ${OBJS_M}

all:		${NAME}

clean:
			${RM} ${OBJS_M} ${OBJS_B} ${OBJS_X}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:		${OBJS_B} ${NAME}
			${AR} ${NAME} ${OBJS_B}

#extra:		${OBJS_X} ${NAME}
#			${AR} ${NAME} ${OBJS_X}
