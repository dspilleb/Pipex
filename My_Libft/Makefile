NAME = libft.a

SRCS = ft_strlen.c ft_strncmp.c ft_strdup.c ft_strjoin.c ft_split.c\
ft_calloc.c ft_strlcpy.c ft_memcpy.c ft_putstr_fd.c

OBJS = ${SRCS:.c=.o}


CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
	@${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
	@${RM} ${OBJS}

fclean:	clean
	@${RM} ${NAME}


re:	fclean all
