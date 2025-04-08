CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

NAME = fdf

SRC	=	ft_printf.c ft_printf_align.c ft_printf_char.c ft_printf_finders.c ft_printf_nbr.c ft_printf_utils.c ft_itoa.c ft_strlen.c ft_memcpy.c ft_memset.c ft_strdub.c \
		get_next_line.c get_next_line_utils.c \
		ft_split.c \
		main.c
OBJS = $(SRC:.c=.o)

$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
bonus: $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)		

re:	fclean all

.PHONY:	all clean fclean re
