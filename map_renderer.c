#include "fdf.h"
#include <stdio.h>


int	gradient_change(int c1, int c2, float t)
{
	int r1, g1, b1;
	int r2, g2, b2;

	r1 = c1 >> 16;
	r2 = c2 >> 16;
	g1 = (c2 >> 8) % 256;
	g2 = (c2 >> 8) % 256;
	b1 = c1 % 256;
	b2 = c2 % 256;
	c1 = 0;
	c1 += (r1 + (r2 - r1) * t);
	c1 = c1 << 8;
	c1 += (g1 + (g2 - g1) * t);
	c1 = c1 << 8;
	c1 += (b1 + (b2 - b1) * t);
	return (c1);
}

void	draw_line(t_point p0, t_point p1, t_data *img)
{
	int dx;
	int dy;
	int err;
	float	i;
	float	n;

	dx = abs(p1.x - p0.x);
	dy = abs(p1.y - p0.y);
	err = dx - dy;
	i = 0;
	n = abs(p1.x - p0.x);
	if (n < abs(p1.y - p0.y))
		n = abs(p1.y - p0.y);
	while (abs(p0.x - p1.x) > 1 || abs(p0.y - p1.y) > 1)
	{
		my_mlx_pixel_put(img, p0.x, p0.y, gradient_change(p0.color, p1.color, i / n));
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
		i++;
	}
}

void rotate_point(t_point *p, t_grid *grid)
{
    float rx = grid->x_angle;
    float ry = grid->y_angle;
    float rz = grid->z_angle;

    float x = p->x;
    float y = p->y;
    float z = p->z;

    float y1 = y * cos(rx) - z * sin(rx);
    float z1 = y * sin(rx) + z * cos(rx);

    float x2 = x * cos(ry) + z1 * sin(ry);
    float z2 = -x * sin(ry) + z1 * cos(ry);

    float x3 = x2 * cos(rz) - y1 * sin(rz);
    float y3 = x2 * sin(rz) + y1 * cos(rz);

    p->x = x3;
    p->y = y3;
    p->z = z2;
}

void project_perspective(t_point *p, float f, int screen_w, int screen_h, t_grid *grid)
{
    float camera_z = -1000.0f; // step back
    float relative_z = p->z - camera_z;
    if (relative_z < 1.0f) relative_z = 1.0f;

    p->x = (p->x * f) / relative_z + screen_w / 2 + grid->x;
    p->y = (p->y * f) / relative_z + screen_h / 2 + grid->y;
}

void	project_isometric(t_point *p, t_grid *grid)
{
	int	x;
	int	y;

	x = p->x - p->y + WIDTH / 2;
	y = (p->x + p->y) / 2 - p->z + HEIGHT / 2;
	p->x = x + grid->x;
	p->y = y + grid->y; 
}

void draw_map(t_grid *grid)
{
	t_data img;
	img.img = mlx_new_image(grid->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	int width = grid->width;
	int height = grid->height;
	int spacing = grid->z;
	float f = 600.0f;
	int i = 0;
	int x0, y0;

	while (i < grid->size)
	{
		int gx = i % width;
		int gy = i / width;

		// Point A
		t_point a;
		a.x = (gx - width / 2) * spacing;
		a.y = (gy - height / 2) * spacing;
		a.z = grid->values[i] * spacing;
		a.color = grid->colors[i];
		if (grid->values[i] != 0)
		    a.z += grid->h_scale;

		rotate_point(&a, grid);
		if (grid->view_mode == 1)
			project_perspective(&a, f, WIDTH, HEIGHT, grid);
		else if (grid->view_mode == 2)
			project_isometric(&a, grid); 
		if (gx < width - 1)
		{
			t_point b;
			int j = i + 1;

			b.x = ((j % width) - width / 2) * spacing;
			b.y = ((j / width) - height / 2) * spacing;
			b.z = grid->values[j] * spacing;
			b.color = grid->colors[i + 1];
			if (grid->values[j] != 0)
				b.z += grid->h_scale;

			rotate_point(&b, grid);
			if (grid->view_mode == 1)
				project_perspective(&b, f, WIDTH, HEIGHT, grid);
			else if (grid->view_mode == 2)
				project_isometric(&b, grid); 
			draw_line(a, b, &img);
		}
		if (gy < height - 1)
		{
			t_point c;
			int j = i + width;

			c.x = ((j % width) - width / 2) * spacing;
			c.y = ((j / width) - height / 2) * spacing;
			c.z = grid->values[j] * spacing;
			c.color = grid->colors[i + width];
			if (grid->values[j] != 0)
				c.z += grid->h_scale;

			rotate_point(&c, grid);
			if (grid->view_mode == 1)
				project_perspective(&c, f, WIDTH, HEIGHT, grid);
			else if (grid->view_mode == 2)
				project_isometric(&c, grid); 
			draw_line(a, c, &img);
		}

		i++;
	}

	mlx_put_image_to_window(grid->mlx, grid->win, img.img, 0, 0);
}
