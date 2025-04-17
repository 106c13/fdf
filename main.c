/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:16 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/17 17:15:40 by haaghaja         ###   ########.fr       */
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
	static double angle = 0.78;	
	static int	zoom = 20;
	t_data	img;

	ft_printf("KEYCODE: %d\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(grid->mlx, grid->win);
		exit(0);
	}
	else if (keycode == 65363)
		angle -= 0.03;
	else if (keycode == 65361)
		angle += 0.03;
	else if (keycode == 65362)
		zoom++;
	else if (keycode == 65364)
		zoom--;	
	if (angle > 2 * PI)
		angle = 0;
	else if (angle < 0)
		angle = 2 * PI;
	if (zoom == 0)
		zoom++;
	draw_map(grid, angle, zoom);
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
		mlx_hook(grid.win, 2, 1L<<0, event_handler, &grid);
		draw_map(&grid, 0.78, 20);
		mlx_loop(grid.mlx);
	}
	return (0);
}
