SDIR			= srcs

_SRCS				=	debug.c \
						get_next_line.c \
						get_next_line_utils.c \
						intersect.c \
						math.c \
						math_vector.c \
						matrix.c \
						ray_tracer.c \
						shade.c \
						utils.c
SRCS				= ${_SRCS:%=${SDIR}/%}
OBJS				= ${_SRCS:.c=.o}

CC					= gcc
# CFLAGS				= -Wall -Werror -Wextra
CFLAGS				=
INC					= -Iheaders -IminilibX
LIB					= lib/
RM					= rm -rf

NAME				= miniRT.a

%.o :				${SDIR}/%.c
					${CC} ${CFLAGS} ${INC} -c -o $@ $<
all :
					cd libft && make
					make ${NAME}
${NAME} :			${OBJS}
					ar rc ${NAME} ${OBJS} libft/*.o
					ln -f ${NAME} ${LIB}${NAME}
clean :
					${RM} ${OBJS}
fclean :			clean
					cd libft && make clean
					${RM} ${NAME}
re :				fclean
					cd libft && make re
					make all
bonus :
					make all
.PHONY :			all clean fclean re bonus
