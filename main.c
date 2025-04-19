/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:16 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/19 16:03:23 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int	event_handler(int keycode, t_grid *grid)
{
	t_data	img;

	ft_printf("KEYCODE: %d\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(grid->mlx, grid->win);
		exit(0);
	}
	else if (keycode == 97)
		grid->x_angle -= 0.03;
	else if (keycode == 100)
		grid->x_angle += 0.03;
	else if (keycode == 119)
		grid->y_angle -= 0.06;
	else if (keycode == 115)
		grid->y_angle += 0.06;
	else if (keycode == 32)
		grid->zoom++;
	else if (keycode == 65289)
		grid->zoom--;
	else if (keycode == 65363)
		grid->x += 8;
	else if (keycode == 65361)
		grid->x -= 8;
	else if (keycode == 65364)
		grid->y += 8;
	else if (keycode == 65362)
		grid->y -= 8;
	if (grid->x_angle > 2 * PI)
		grid->x_angle = 0;
	else if (grid->x_angle < 0)
		grid->x_angle = 2 * PI;
	if (grid->zoom == 0)
		grid->zoom++;
	draw_map(grid);
	return (1);
}

int	main(int argc, char **argv)
{
	t_grid	grid;

	if (argc == 2)
	{
		if (!create_grid(argv[1], &grid))
			return (0);
		ft_printf("W: %d H: %d\n", grid.width, grid.height);
		grid.mlx = mlx_init();
		grid.win = mlx_new_window(grid.mlx, WIDTH, HEIGHT, "Hello world!");
		grid.x = 500;
		grid.y = 500;
		grid.x_angle = 0;
		grid.y_angle = 0;
		grid.z_angle = 0;
		grid.zoom = 20;
		mlx_hook(grid.win, 2, 1L<<0, event_handler, &grid);
		draw_map(&grid);
		mlx_loop(grid.mlx);
	}
	return (0);
}
