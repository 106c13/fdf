/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:16 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/26 18:39:31 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_exit(void *param)
{
	t_grid	*grid;

	grid = (t_grid *)param;
	free(grid->points);
	free(grid->o_points);
	free(grid->selected_points);
	mlx_destroy_image(grid->mlx, grid->img->img);
	mlx_destroy_window(grid->mlx, grid->win);
	mlx_destroy_display(grid->mlx);
	free(grid->mlx);
	exit(0);
	return (1);
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
		grid.win = mlx_new_window(grid.mlx, WIDTH, HEIGHT, "FDF");
		img.img = mlx_new_image(grid.mlx, WIDTH, HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.b, &img.l, &img.endian);
		grid.img = &img;
		mlx_hook(grid.win, 2, 1L << 0, event_handler, &grid);
		mlx_hook(grid.win, 17, 0, fdf_exit, &grid);
		obj_init(&grid);
		draw_map(&grid, 0);
		draw_menu(&grid);
		mlx_loop(grid.mlx);
	}
	else
		ft_printf("Usage: ./fdf <file_name>\n");
	return (0);
}
