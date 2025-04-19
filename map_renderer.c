#include "fdf.h"
#include <stdio.h>

void	draw_line(int x0, int y0, int x1, int y1, t_data *img)
{
	int dx;
	int dy;
	int err;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
	while (x0 != x1 || y0 != y1)
	{
		my_mlx_pixel_put(img, x0, y0, 0xffffff);
		if (err > -dy)
		{
			err -= dy;
			if (x0 < x1)
				x0++;
			else
				x0--;
		}
		if (err < dx)
		{
			err += dx;
			if (y0 < y1)
				y0++;
			else
				y0--;
		}
	}
}

void	draw_map(t_grid *grid)
{
	t_data	img;
	int	i;
	int	x0, x1, y0, y1, z0, z1;
	int	dx, dy;
	int	d;

	img.img = mlx_new_image(grid->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	i = 0;
	int width = grid->width;
	int height = grid->height;
	while (i < grid->size)
	{
		x1 = -(width - 2 * (i % width) - 1) * grid->z;// * cos(grid->y_angle);
		y1 = -(height - 2 * (i / width) - 1) * grid->z;// * sin(grid->y_angle);
		dx = x1 * cos(grid->x_angle) - y1 * sin(grid->x_angle);
		dy = x1 * sin(grid->x_angle) + y1 * cos(grid->x_angle);
		x0 = grid->x + dx;
		y0 = grid->y + dy;
		if (i % width  < width - 1)
		{
			x1 = -(width - 2 * ((i + 1) % width) - 1) * grid->z;
			y1 = -(height - 2 * ((i + 1) / width) - 1) * grid->z;
			dx = x1 * cos(grid->y_angle) - y1 * sin(grid->x_angle);
			dy = x1 * sin(grid->y_angle) + y1 * cos(grid->x_angle);
			x1 = grid->x + dx;
			y1 = grid->y + dy;
			//draw_line(x0, y0, x1, y1, &img);
		}
		if (i / width < height - 1)
		{
			x1 = -(width - 2 * ((i + width) % width) - 1) * grid->z;
			y1 = -(height - 2 * ((i + width) / width) - 1) * grid->z;
			dx = x1 * cos(grid->y_angle) - y1 * sin(grid->x_angle);
			dy = x1 * sin(grid->y_angle) + y1 * cos(grid->x_angle);
			x1 = grid->x + dx;
			y1 = grid->y + dy;
			//draw_line(x0, y0, x1, y1, &img);
		}
		my_mlx_pixel_put(&img, x0, y0, 0xffffff);
		i++;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, img.img, 0, 0);
}

