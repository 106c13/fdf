CC = cc
#CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

NAME = fdf
OBJDIR = objs


# MLX stuff
INC=/usr/include
INCLIB=$(INC)/../lib
CFLAGS= -I$(INC) -O3 -Imlx -g
LFLAGS = -Lmlx -lmlx -L$(INCLIB) -lXext -lX11 -lm


SRC = ft_printf.c ft_printf_align.c ft_printf_char.c ft_printf_finders.c ft_printf_nbr.c ft_printf_utils.c ft_itoa.c ft_strlen.c ft_memcpy.c ft_memset.c ft_strdub.c \
      get_next_line.c get_next_line_utils.c \
      ft_split.c \
      validator.c error_handlers.c utils.c parser.c map_renderer.c \
      main.c

OBJS = $(SRC:.c=.o)
OBJS := $(OBJS:%=$(OBJDIR)/%)


all: $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -Imlx -I/usr/include -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS)

${OBJDIR}:
	mkdir -p ${OBJDIR}

clean:
	$(RM) $(OBJDIR)

# Clean up object files, executable, and the OBJDIR
fclean: clean
	$(RM) $(NAME)

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
