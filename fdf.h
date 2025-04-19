/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:07:55 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/19 14:25:53 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H


# define PI 3.14
# define WIDTH 1000
# define HEIGHT 1000

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "get_next_line.h"
#include "mlx/mlx.h"
// TODO: remove this V
#include "ft_printf.h"

typedef struct s_grid
{
	void	*mlx;
	void	*win;
	int	width;
	int	height;
	int	size;
	int	x;
	int	y;
	int	z;
	double	x_angle;
	double	y_angle;
	double	z_angle;	
	int	*values;
	int	*colors;
} t_grid;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// ft_splic.c
char	**ft_split(char *str, char sep);

// validator.c
int	get_grid_size(int fd);

// parser.c
int	create_grid(char *fnamem, t_grid *grid);

// map_renderer.c
void	draw_map(t_grid *grid);

// utils.c
int	ft_htod(char **str);

// main.c
int	error(char *str, int out);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// error_handlers.c
void	*error_ptr(char *msg, void *ptr);
int	error(char *msg, int error_code);

#endif
