SRCS 	= main.c mandelbrot.c julia.c events.c utils.c z2plusc2.c complex_plan_manager.c color_manager.c

OBJS	= ${SRCS:.c=.o}

NAME	= fractol

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -Imlx -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C libft
			$(CC) $^ -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework Appkit -o $(NAME)

all:		${NAME}

clean:		
			make clean -C libft
			${RM} ${OBJS}

fclean:		clean
			make fclean -C libft
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re