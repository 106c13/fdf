/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:00:45 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/29 13:55:56 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define PI 3.14
# define WIDTH 1500
# define HEIGHT 1000

# define X_MIN 0
# define Y_MIN 0
# define X_MAX WIDTH
# define Y_MAX HEIGHT

# define INSIDE 0
# define LEFT   1
# define RIGHT  2
# define BOTTOM 4
# define TOP    8

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
	t_point	*o_points;
}	t_grid;

typedef struct s_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
	int	color;
}	t_rect;

// ft_splic.c
char	**ft_split(char *str, char sep);

// validator.c
int		get_grid_size(int fd);
int		is_valid_symbol(char c, char *s);

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
void	reset_img(t_data *img);
int		ft_printf(char *str);
int		ft_htod(char **str);
int		get_color(int i);
int		gradient(int c1, int c2, float t);

void	obj_reset(t_grid *grid);
void	obj_init(t_grid *grid);
void	obj_reset(t_grid *grid);
void	unselect_all(t_grid *grid);
t_point	create_point(t_grid *grid, int i, int edit_mode);

int		is_int(char **str);
int		get_sign(char **str);

// main.c
int		error(char *str, int out);
int		fdf_exit(void *param);

// error_handlers.c
void	*error_ptr(char *msg, void *ptr);
int		error(char *msg, int error_code);

// window.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_menu(t_grid *grid);
void	change_height(t_grid *grid, int value);

// fdf_draw.c
void	draw_fdf(t_data *img);

// handler.c
void	editor_handler(int keycode, t_grid *grid);
void	grid_setting_handler(int keycode, t_grid *grid);
void	rotation_handler(int keycode, t_grid *grid, int edit_mode);
int		event_handler(int keycode, t_grid *grid);

#endif
