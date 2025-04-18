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

void	draw_map(t_grid *grid, double angle, int zoom, int x, int y)
{
	t_data	img;
	int	i;
	int	x0, x1, y0, y1;
	int	dx, dy;
	int	gw;
	int	d;

	img.img = mlx_new_image(grid->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	i = 0;
	gw = 500 / grid->width / 2;
	d = 1;
	int width = grid->width;
	int height = grid->height;
	//zoom = 5;	
	while (i < grid->size)
	{
		dx = -(width - 2 * (i % width) - 1) * d * zoom;
		dy = -(height - 2 * (i / width) - 1) * d * zoom;
		x0 = x + dx * cos(angle) - dy * sin(angle);
		y0 = y + dx * sin(angle) + dy * cos(angle);
		if (i % width  < width - 1)
		{
			dx = -(width - 2 * ((i + 1) % width) - 1) * d * zoom;
			dy = -(height - 2 * ((i + 1) / width) - 1) * d * zoom;
			x1 = x + dx * cos(angle) - dy * sin(angle);
			y1 = y + dx * sin(angle) + dy * cos(angle);
			draw_line(x0, y0, x1, y1, &img);
		}
		if (i / width < height - 1)
		{
			dx = -(width - 2 * ((i + width) % width) - 1) * d * zoom;
			dy = -(height - 2 * ((i + width) / width) - 1) * d * zoom;
			x1 = x + dx * cos(angle) - dy * sin(angle);
			y1 = y + dx * sin(angle) + dy * cos(angle);
			draw_line(x0, y0, x1, y1, &img);
		}
		i++;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, img.img, 0, 0);
	return ;
	x = 500;
	y = 500;
	my_mlx_pixel_put(&img, x, y, 0xffffff);
	// Draw a line between dots
	d = 5;
	x0 = x + zoom * (d * cos(angle) - 0 * sin(angle));
	y0 = y + zoom * (d * sin(angle) + 0 * cos(angle));
	x1 = x + zoom * (0 * cos(angle) - d * sin(angle));
	y1 = y + zoom * (0 * sin(angle) + d * cos(angle));
	draw_line(x0, y0, x1, y1, &img);
	x0 = x + zoom * (0 * cos(angle) - d * sin(angle));
	y0 = y + zoom * (0 * sin(angle) + d * cos(angle));
	x1 = x + zoom * (-d * cos(angle) - 0 * sin(angle));
	y1 = y + zoom * (-d * sin(angle) + 0 * cos(angle));
	draw_line(x0, y0, x1, y1, &img);
	x0 = x + zoom * (-d * cos(angle) - 0 * sin(angle));
	y0 = y + zoom * (-d * sin(angle) + 0 * cos(angle));
	x1 = x + zoom * (0 * cos(angle) - (-d) * sin(angle));
	y1 = y + zoom * (0 * sin(angle) + (-d) * cos(angle));
	draw_line(x0, y0, x1, y1, &img);
	x0 = x + zoom * (d * cos(angle) - 0 * sin(angle));
	y0 = y + zoom * (d * sin(angle) + 0 * cos(angle));
	draw_line(x0, y0, x1, y1, &img);
	
	x1 = x + zoom * (2 * d * cos(angle) - d * sin(angle));
	y1 = y + zoom * (2 * d * sin(angle) + d * cos(angle));
	draw_line(x0, y0, x1, y1, &img);
	my_mlx_pixel_put(&img, x1, y1, 0xff0000);
	mlx_put_image_to_window(grid->mlx, grid->win, img.img, 0, 0);
}

