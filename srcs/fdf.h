#ifndef FDF_H
# define FDF_H

# define PI 3.14
# define WIDTH 1500
# define HEIGHT 1000

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "get_next_line.h"
# include "../mlx/mlx.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		b;
	int		l;
	int		endian;
}	t_data;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

typedef struct s_grid
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int		size;
	int		x;
	int		y;
	float	zoom;
	int		view_mode;
	int		*selected_points;
	int		s_point;
	t_data	*img;
	t_point	*points;
}	t_grid;

// ft_splic.c
char	**ft_split(char *str, char sep);

// validator.c
int		get_grid_size(int fd);

// parser.c
int		create_grid(char *fnamem, t_grid *grid);

// view.c
void	project_perspective(t_point *p, float f, t_grid *grid);
void	project_isometric(t_point *p, t_grid *grid);
void	rotate_x(t_grid *grid, float angle);
void	rotate_y(t_grid *grid, float angle);
void	rotate_z(t_grid *grid, float angle);

// grid.c
void	unselect_all(t_grid *grid);
void	draw_map(t_grid *grid, int edit_mode);
void	obj_init(t_grid *grid);
t_point	create_point(t_grid *grid, int i, int edit_mode);

// utils.c
int		ft_printf(char *str);
int		ft_htod(char **str);
int		get_color(int i);
int		gradient_change(int c1, int c2, float t);
void	reset_img(t_data *img);

// main.c
int		error(char *str, int out);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// error_handlers.c
void	*error_ptr(char *msg, void *ptr);
int		error(char *msg, int error_code);

// window.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_menu(t_grid *grid);
void	change_height(t_grid *grid, int value);

#endif
