SDIR				=	srcs
_SRCS				=	draw.c \
						events.c \
						get_next_line.c \
						get_next_line_utils.c \
						intersect.c \
						intersect_obj1.c \
						intersect_obj2.c \
						intersect_utils.c \
						main.c \
						math.c \
						math_vector1.c \
						math_vector2.c \
						matrix1.c \
						matrix2.c \
						matrix3.c \
						matrix4.c \
						parsing.c \
						parsing_linesanity1.c \
						parsing_linesanity2.c \
						parsing_obj1.c \
						parsing_obj2.c \
						parsing_strsanity1.c \
						parsing_strsanity2.c \
						ray_tracer1.c \
						ray_tracer2.c \
						save.c \
						shade1.c \
						shade2.c \
						utils1.c \
						utils2.c \
						utils3.c \
						utils_mlx.c \
						utils_parsing.c \
						utils_sanity.c
SRCS				= ${_SRCS:%=${SDIR}/%}
OBJS				= ${_SRCS:.c=.o}
CC					= clang
CFLAGS				= -g -Wall -Werror -Wextra
INC					= -Iheaders -IminilibX -Ilibft
RM					= rm -rf
NAME				= miniRT

%.o :				${SDIR}/%.c
					${CC} ${CFLAGS} ${INC} -c -o $@ $<
all :
					cd libft && make
					cd minilibX && make
					make ${NAME}
${NAME} :			${OBJS}
					${CC} -o ${NAME} ${OBJS} libft/libft.a minilibX/libmlx.a -lXext -lX11 -lm
clean :
					cd libft && make clean
					cd minilibX && make clean
					${RM} ${OBJS}
fclean :			clean
					cd libft && make fclean
					${RM} ${NAME}
					${RM} ${LIB}${NAME} ${LIB}libft.a
re :				fclean
					cd libft && make re
					make all
bonus :
					make all
.PHONY :			all clean fclean re bonus
