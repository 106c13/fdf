CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf 

NAME = fdf 
OBJDIR = objs

# MLX stuff
INC = /usr/include
INCLIB = $(INC)/../lib
CFLAGS = -I$(INC) -O3 -Imlx -g
LFLAGS = -Lmlx -lmlx -L$(INCLIB) -lXext -lX11 -lm 

# Source files
SRC = srcs/get_next_line.c srcs/get_next_line_utils.c \
      srcs/ft_split.c \
      srcs/validator.c srcs/error_handlers.c srcs/utils.c srcs/parser.c srcs/grid.c srcs/view.c \
      srcs/main.c

# Object files - convert source files to object files and store them in the 'objs' directory
OBJS = $(SRC:srcs/%.c=$(OBJDIR)/%.o)

# Default target
all: $(NAME)

# Compile object files
$(OBJDIR)/%.o: srcs/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the executable
$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS)

# Create the 'objs' directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up object files
clean:
	$(RM) $(OBJDIR)

# Clean up object files and executable
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re

