#include "fdf.h"
#include <stdio.h>

void	draw_line(t_point p0, t_point p1, t_data *img)
{
	int dx;
	int dy;
	int err;
	int	c;

	dx = abs(p1.x - p0.x);
	dy = abs(p1.y - p0.y);
	err = dx - dy;
	while (p0.x != p1.x || p0.y != p1.y)
	{
		my_mlx_pixel_put(img, p0.x, p0.y, p0.color);
		if (err > -dy)
		{
			err -= dy;
			if (p0.x < p1.x)
				p0.x++;
			else
				p0.x--;
		}
		if (err < dx)
		{
			err += dx;
			if (p0.y < p1.y)
				p0.y++;
			else
				p0.y--;
		}
		//if (p0.color < p1.color)
	//		p0.color += (p1.color - p0.color)/7;
	}
}

void	draw_map(t_grid *grid)
{
	t_data	img;
	int	i;
	int	x0, x1, y0, y1, z0, z1;
	int	dx, dy, dz;
	int	dtx, dty;
	int	d;
	int	factor;
	int	dis;
	t_point	p0;
	t_point	p1;
	img.img = mlx_new_image(grid->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	i = 0;
	d = grid->z;

	int width = grid->width;
	int height = grid->height;
	while (i < grid->size)
	{
		x0 = -(width - 2 * (i % width) - 1) * d;
		y0 = -(height - 2 * (i / width) - 1) * d;
		dx = x0 * cos(grid->z_angle) - y0 * sin(grid->z_angle);
		dy = x0 * sin(grid->z_angle) + y0 * cos(grid->z_angle);
		dz = 0;

		dy = x0 * cos(grid->x_angle) - z0 * sin(grid->x_angle);
		dy = x0 * sin(grid->x_angle) + z0 * cos(grid->x_angle);
		dis = 10;
		factor = dis/(dis + dz);	
		x0 = grid->x + dx * factor;
		y0 = grid->y + dy * factor;
		printf("%f %f\n", grid->x_angle, grid->z_angle);
		if (i % width < width - 1)
		{
			x1 = -(width - 2 * ((i + 1) % width) - 1) * d;
			y1 = -(height - 2 * ((i + 1) / width) - 1) * d;
			dx = x1 * cos(grid->z_angle) - y1 * sin(grid->z_angle);
			dy = x1 * sin(grid->z_angle) + y1 * cos(grid->z_angle);
			dz = 0;

			dy = x1 * cos(grid->x_angle) - z0 * sin(grid->x_angle);
			dy = x1 * sin(grid->x_angle) + z0 * cos(grid->x_angle);
			dis = 10;
			factor = dis/(dis + dz);	
			x1 = grid->x + dx * factor;
			y1 = grid->y + dy * factor;
			
			p0.x = x0;
			p0.y = y0;
			p0.color = grid->colors[i];
			p1.x = x1;
			p1.y = y1;
			p1.color = grid->colors[i + 1];
			//printf("=%d %d %d %d\n", p0.x, p0.y, p1.x, p1.y);
			draw_line(p0, p1, &img);
		}
		if (i / width < height - 1)
		{
			x1 = -(width - 2 * ((i + width) % width) - 1) * grid->z;
			y1 = -(height - 2 * ((i + width) / width) - 1) * grid->z;
			dx = x1 * cos(grid->z_angle) - y1 * sin(grid->z_angle);
			dy = x1 * sin(grid->z_angle) + y1 * cos(grid->z_angle);
			dz = 0;

			dy = x1 * cos(grid->x_angle) - z0 * sin(grid->x_angle);
			dy = x1 * sin(grid->x_angle) + z0 * cos(grid->x_angle);
			dis = 10;
			factor = dis/(dis + dz);	
			x1 = grid->x + dx * factor;
			y1 = grid->y + dy * factor;
			
			p0.x = x0;
			p0.y = y0;
			p0.color = grid->colors[i];
			p1.x = x1;
			p1.y = y1;
			p1.color = grid->colors[i + width];
			//printf("=%d %d %d %d\n", p0.x, p0.y, p1.x, p1.y);
			draw_line(p0, p1, &img);
		}
		//my_mlx_pixel_put(&img, x0, y0, grid->colors[i]);
		i++;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, img.img, 0, 0);
}

