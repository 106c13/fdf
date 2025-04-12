CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

NAME = fdf
OBJDIR = objs

SRC = ft_printf.c ft_printf_align.c ft_printf_char.c ft_printf_finders.c ft_printf_nbr.c ft_printf_utils.c ft_itoa.c ft_strlen.c ft_memcpy.c ft_memset.c ft_strdub.c \
      get_next_line.c get_next_line_utils.c \
      ft_split.c \
      validator.c error_handlers.c utils.c parser.c \
      main.c

OBJS = $(SRC:.c=.o)
OBJS := $(OBJS:%=$(OBJDIR)/%)


all: $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -Imlx_linux -I/usr/include -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

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
