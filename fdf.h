/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:07:55 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/12 14:57:25 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include "get_next_line.h"
#include "mlx/mlx.h"
// TODO: remove this V
#include "ft_printf.h"

typedef struct s_grid
{
	int	width;
	int	height;
	int	size;
	int	*values;
	int	*colors;
	struct s_grid	*next;
} t_grid;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

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
void	draw_map(t_grid *grid, t_vars *vars);

// utils.c
int	ft_htod(char **str);

// main.c
int	error(char *str, int out);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// error_handlers.c
void	*error_ptr(char *msg, void *ptr);
int	error(char *msg, int error_code);

#endif
