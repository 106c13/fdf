CC = cc
RM = rm -rf 

NAME = fdf 
OBJDIR = objs

# MLX stuff
INC = /usr/include
INCLIB = $(INC)/../lib
CFLAGS = -I$(INC) -O3 -Imlx -g 
LFLAGS = -Lmlx -lmlx -L$(INCLIB) -lXext -lX11 -lm 

SRC = srcs/get_next_line.c srcs/get_next_line_utils.c \
      srcs/window.c srcs/utils2.c srcs/fdf_draw.c srcs/handlers.c \
      srcs/validator.c srcs/error_handlers.c srcs/utils.c srcs/parser.c srcs/grid.c srcs/view.c \
      srcs/main.c

OBJS = $(SRC:srcs/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR)/%.o: srcs/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS) $(CFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

