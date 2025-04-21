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

void rotate_point(t_point *point, t_grid *grid)
{
    float rx = grid->x_angle;
    float ry = grid->y_angle;
    float rz = grid->z_angle;

    float tx, ty, tz;

    // Rotate around X axis (pitch)
    ty = point->y * cos(rx) - point->z * sin(rx);
    tz = point->y * sin(rx) + point->z * cos(rx);
    point->y = ty;
    point->z = tz;

    // Rotate around Y axis (yaw)
    tx = point->x * cos(ry) + point->z * sin(ry);
    tz = -point->x * sin(ry) + point->z * cos(ry);
    point->x = tx;
    point->z = tz;

    // Rotate around Z axis (roll)
    tx = point->x * cos(rz) - point->y * sin(rz);
    ty = point->x * sin(rz) + point->y * cos(rz);
    point->x = tx;
    point->y = ty;
}

void draw_map(t_grid *grid)
{
	t_data img;
	t_point	point;
	t_point point1;

	img.img = mlx_new_image(grid->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	int width = grid->width;
	int height = grid->height;
	int x0, y0, i = 0;
	int gx, gy;
	int spacing = grid->z; // distance between points on grid
	//printf("%f %f %f\n", grid->x_angle, grid->y_angle, grid->z_angle);
	while (i < grid->size)
	{
		gx = i % width;
		gy = i / width;
		point.x = (gx - width / 2) * spacing;
		point.y = (gy - height / 2) * spacing;
		point.z = grid->values[i] * spacing;
		rotate_point(&point, grid);
		x0 = point.x - point.y + WIDTH / 2;
		y0 = (point.x + point.y) / 2 - point.z + HEIGHT / 2;
		point.x = x0;
		point.y = y0;
		if (i % width < width - 1)
		{	
			gx = (i + 1) % width;
			gy = (i + 1) / width;
			point1.x = (gx - width / 2) * spacing;
			point1.y = (gy - height / 2) * spacing;
			point1.z = grid->values[i+1] * spacing;
			rotate_point(&point1, grid);
			x0 = point1.x - point1.y + WIDTH / 2;
			y0 = (point1.x + point1.y) / 2 - point1.z + HEIGHT / 2;
			point1.x = x0;
			point1.y = y0;
			draw_line(point, point1, &img);
		}
		if (i / width < height - 1)
		{	
			gx = (i + width) % width;
			gy = (i + width) / width;
			point1.x = (gx - width / 2) * spacing;
			point1.y = (gy - height / 2) * spacing;
			point1.z = grid->values[i +  width] * spacing;
			rotate_point(&point1, grid);
			x0 = point1.x - point1.y + WIDTH / 2;
			y0 = (point1.x + point1.y) / 2 - point1.z + HEIGHT / 2;
			point1.x = x0;
			point1.y = y0;
			draw_line(point, point1, &img);
		}
		//my_mlx_pixel_put(&img, point.x, point.y, grid->colors[i]);
		i++;
	}

	mlx_put_image_to_window(grid->mlx, grid->win, img.img, 0, 0);
}
