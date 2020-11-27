SRCS		=	ft_atof.c \
				ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_isspht.c \
				ft_itoa.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_pow.c \
				ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putint_fd.c \
				ft_putnbr_fd.c \
				ft_putnstr.c \
				ft_putstr.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_splitf.c \
				ft_splits.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c
B_SRCS		= ./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstsize.c ./ft_lstlast.c ./ft_lstadd_back.c ./ft_lstdelone.c ./ft_lstclear.c ./ft_lstiter.c ./ft_lstmap.c
OBJS		= ${SRCS:.c=.o}
B_OBJS		= ${B_SRCS:.c=.o}
CC			= clang
CFLAGS		= -Wall -Wextra -Werror
NAME		= libft.a
RM			= rm -f

all :		${OBJS}
			make ${NAME}
${NAME} :	${OBJS}
			ar rc ${NAME} ${OBJS}
bonus :		${OBJS} ${B_OBJS}
			ar rc ${NAME} ${OBJS} ${B_OBJS}
clean :
			${RM} ${OBJS} ${B_OBJS}
fclean :	clean
			${RM} ${NAME}
re :
			make fclean
			make all
.PHONY	:
			all ${NAME} clean fclean re bonus
