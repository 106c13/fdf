/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:16 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/12 15:30:22 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int	event_handler(int keycode, t_vars *vars)
{
	t_data	img;

	ft_printf("KEYCODE: %d\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_grid	grid;
	t_vars	vars;
	int	width = 500;
	int	height = 500;

	if (argc == 2)
	{
		if (!create_grid(argv[1], &grid))
			return (0);
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, width, height, "Hello world!");
		mlx_hook(vars.win, 2, 1L<<0, event_handler, &vars);
		draw_map(&grid, &vars);
		mlx_loop(vars.mlx);
	}
	return (0);
}
