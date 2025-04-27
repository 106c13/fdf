CC     = cc
RM     = rm -rf

NAME   = fdf
OBJDIR = objs
MLX_LIB = mlx/libmlx.a

# MLX (MiniLibX) configuration
INC    = /usr/include
INCLIB = $(INC)/../lib
CFLAGS = -I$(INC) -Imlx -O3 -g -Wall -Wextra -Werror
LFLAGS = -Lmlx -lmlx -L$(INCLIB) -lXext -lX11 -lm

SRC    = srcs/get_next_line.c srcs/get_next_line_utils.c \
         srcs/window.c srcs/utils2.c srcs/fdf_draw.c srcs/handlers.c \
         srcs/validator.c srcs/error_handlers.c srcs/utils.c srcs/parser.c srcs/grid.c srcs/view.c \
         srcs/main.c

OBJS   = $(SRC:srcs/%.c=$(OBJDIR)/%.o)

# Main targets
all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)

$(MLX_LIB):
	$(MAKE) -C mlx

$(OBJDIR)/%.o: srcs/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(MAKE) -C mlx clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
