/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:16 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/22 14:37:34 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_handler(int keycode, t_grid *grid, int edit_mode)
{
	if (keycode == 97)
		rotate_z(grid, -0.1);
	else if (keycode == 100)
		rotate_z(grid, 0.1);
	else if (keycode == 119)
		rotate_x(grid, -0.1);
	else if (keycode == 115)
		rotate_x(grid, 0.1);
	else if (keycode == 113)
		rotate_y(grid, -0.1);
	else if (keycode == 101)
		rotate_y(grid, 0.1);
}

void	grid_setting_handler(int keycode, t_grid *grid)
{
	if (keycode == 32)
		grid->zoom += 0.1;
	else if (keycode == 65289)
		grid->zoom -= 0.1;
	else if (keycode == 65363)
		grid->x += 8;
	else if (keycode == 65361)
		grid->x -= 8;
	else if (keycode == 65364)
		grid->y += 8;
	else if (keycode == 65362)
		grid->y -= 8;
	else if (keycode == 61)
		change_height(grid, 1);
	else if (keycode == 45)
		change_height(grid, -1);
	else if (keycode == 49)
		grid->view_mode = 1;
	else if (keycode == 50)
		grid->view_mode = 2;
}

void	editor_handler(int keycode, t_grid *grid)
{
	if (keycode == 99)
	{
		grid->selected_points[grid->s_point]++;
		grid->selected_points[grid->s_point] %= 2;
	}
	else if (keycode == 120)
		unselect_all(grid);
	else if (keycode == 107 && grid->s_point + grid->width < grid->size)
		grid->s_point += grid->width;
	else if (keycode == 105 && grid->s_point - grid->width >= 0)
		grid->s_point -= grid->width;
	else if (keycode == 106 && grid->s_point != 0)
		grid->s_point -= 1;
	else if (keycode == 108 && grid->s_point != grid->size - 1)
		grid->s_point += 1;
}

int	event_handler(int keycode, t_grid *grid)
{
	static int	edit_mode;

	if (keycode == 65307)
	{
		mlx_destroy_window(grid->mlx, grid->win);
		exit(0);
	}
	else if (keycode == 118)
	{
		edit_mode++;
		edit_mode %= 2;
	}
	rotation_handler(keycode, grid, edit_mode);
	grid_setting_handler(keycode, grid);
	editor_handler(keycode, grid);
	if (grid->zoom < 0.1)
		grid->zoom = 0.1;
	draw_map(grid, edit_mode);
	draw_menu(grid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_grid	grid;
	t_data	img;

	if (argc == 2)
	{
		if (!create_grid(argv[1], &grid))
			return (0);
		grid.mlx = mlx_init();
		grid.win = mlx_new_window(grid.mlx, WIDTH, HEIGHT, "Hello world!");
		img.img = mlx_new_image(grid.mlx, WIDTH, HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.b, &img.l, &img.endian);
		grid.img = &img;
		mlx_hook(grid.win, 2, 1L << 0, event_handler, &grid);
		obj_init(&grid);
		draw_map(&grid, 0);
		draw_menu(&grid);
		mlx_loop(grid.mlx);
	}
	else
		ft_printf("Usage: ./fdf <map>\n");
	return (0);
}
