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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(int *)dst = color;
	}
}

void draw_menu(t_grid *grid)
{
    int x;
    int y;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH/7; x++)
        {
            my_mlx_pixel_put(grid->img, x, y, 0x2f4b71);
        }
    }
    mlx_string_put(grid->mlx, grid->win, 40, 20, 0xFFFFFF, "Menu");
    mlx_string_put(grid->mlx, grid->win, 40, 60, 0xe5e5df, "X: Left/Right");
    mlx_string_put(grid->mlx, grid->win, 40, 80, 0xe5e5df, "Y: Up/Down");
    mlx_string_put(grid->mlx, grid->win, 40, 120, 0xe5e5df, "X angle: W S");
    mlx_string_put(grid->mlx, grid->win, 40, 140, 0xe5e5df, "Y angle: Q E");
    mlx_string_put(grid->mlx, grid->win, 40, 160, 0xe5e5df, "Z angle: A D");
    mlx_string_put(grid->mlx, grid->win, 40, 200, 0xe5e5df, "Zoom in/out: Space/Tab");
    mlx_string_put(grid->mlx, grid->win, 40, 240, 0xe5e5df, "Perspective: 1");
    mlx_string_put(grid->mlx, grid->win, 40, 260, 0xe5e5df, "Isometric: 2");
    mlx_string_put(grid->mlx, grid->win, 40, 320, 0xe5e5df, "Editor Mode");
    mlx_string_put(grid->mlx, grid->win, 40, 340, 0xe5e5df, "Enter/Exit: V");
    mlx_string_put(grid->mlx, grid->win, 40, 360, 0xe5e5df, "Select point: C");
    mlx_string_put(grid->mlx, grid->win, 40, 380, 0xe5e5df, "Deselect point: C");
    mlx_string_put(grid->mlx, grid->win, 40, 400, 0xe5e5df, "Deselect all: X");
    mlx_string_put(grid->mlx, grid->win, 40, 420, 0xe5e5df, "Increase height: +");
    mlx_string_put(grid->mlx, grid->win, 40, 440, 0xe5e5df, "Decrease height: -");
    mlx_string_put(grid->mlx, grid->win, 40, 490, 0xe5e5df, "Move Left: J");
    mlx_string_put(grid->mlx, grid->win, 40, 510, 0xe5e5df, "Move Right: L");
    mlx_string_put(grid->mlx, grid->win, 40, 530, 0xe5e5df, "Move Up: I");
    mlx_string_put(grid->mlx, grid->win, 40, 550, 0xe5e5df, "Move Down: K");
}






void	change_height(t_grid *grid, int value)
{
	int	i;

	i = 0;
	while (i < grid->size)
	{
		if (grid->selected_points[i] != 0)
			grid->values[i] += value;
		i++;
	}
}

void	unselect_all(t_grid *grid)
{
	int	i;

	i = 0;
	while (i < grid->size)
	{
		grid->selected_points[i] = 0;
		i++;
	}
}

int	event_handler(int keycode, t_grid *grid)
{
	static int edit_mode;

	if (keycode == 65307)
	{
		mlx_destroy_window(grid->mlx, grid->win);
		exit(0);
	}
	else if (keycode == 97)
		grid->z_angle -= 0.1;
	else if (keycode == 100)
		grid->z_angle += 0.1;
	else if (keycode == 119)
		grid->x_angle -= 0.1;
	else if (keycode == 115)
		grid->x_angle += 0.1;
	else if (keycode == 113)
		grid->y_angle -= 0.1;
	else if (keycode == 101)
		grid->y_angle += 0.1;
	else if (keycode == 32)
		grid->z += 1;
	else if (keycode == 65289)
		grid->z -= 1;
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
	{
		grid->x_angle = PI / 4;
		grid->y_angle = 0;
		grid->z_angle = PI;
		grid->view_mode = 1;
	}
	else if (keycode == 50)
	{
		grid->x_angle = 0;
		grid->y_angle = 0;
		grid->z_angle = 0;
		grid->view_mode = 2;
	}
	else if (keycode == 118)
	{
		edit_mode++;
		edit_mode %= 2;
	}
	else if (keycode == 99)
	{
		grid->selected_points[grid->s_point]++;
		grid->selected_points[grid->s_point] %= 2;
	}
	else if (keycode == 120)
		unselect_all(grid);
	else if (keycode == 107)
	{
		if (grid->s_point + grid->width < grid->size)
			grid->s_point += grid->width;
	}
	else if (keycode == 105)
	{
		if (grid->s_point - grid->width >= 0)
			grid->s_point -= grid->width;
	}
	else if (keycode == 106)
	{
		if (grid->s_point != 0)
			grid->s_point -= 1;
	}
	else if (keycode == 108)
	{
		if (grid->s_point != grid->size - 1)
			grid->s_point += 1;
	}
	if (grid->z < 1)
		grid->z = 1;
	draw_map(grid, edit_mode);
	draw_menu(grid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_grid	grid;
	t_data img;
	
	if (argc == 2)
	{
		if (!create_grid(argv[1], &grid))
			return (0);
		grid.mlx = mlx_init();
		grid.win = mlx_new_window(grid.mlx, WIDTH, HEIGHT, "Hello world!");
		grid.x = 0;
		grid.y = 0;
		grid.z = 15;
		grid.h_scale = 1;
		grid.view_mode = 2;
		grid.flag = 1;
		grid.s_point = 0;
		img.img = mlx_new_image(grid.mlx, WIDTH, HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
		grid.img = &img;
		mlx_hook(grid.win, 2, 1L<<0, event_handler, &grid);
		draw_map(&grid, 0);
		draw_menu(&grid);
		mlx_loop(grid.mlx);
	}
	return (0);
}
