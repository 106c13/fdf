#include "fdf.h"
#include <stdio.h>

int	gradient_change(int c1, int c2, float t)
{
	int r1, g1, b1;
	int r2, g2, b2;

	if (c1 == c2 || t == 0)
		return (c1);
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

void rotate_x(t_grid *grid, float angle) {
    float c = cos(angle);
    float s = sin(angle);

    for (int i = 0; i < grid->size; i++) {
        t_point *p = &grid->points[i];
        float y = p->y;
        float z = p->z;
        p->y = y * c - z * s;
        p->z = y * s + z * c;
    }
}

void rotate_y(t_grid *grid, float angle) {
    float c = cos(angle);
    float s = sin(angle);

    for (int i = 0; i < grid->size; i++) {
        t_point *p = &grid->points[i];
        float x = p->x;
        float z = p->z;
        p->x = x * c + z * s;
        p->z = -x * s + z * c;
    }
}

void rotate_z(t_grid *grid, float angle) {
    float c = cos(angle);
    float s = sin(angle);

    for (int i = 0; i < grid->size; i++) {
        t_point *p = &grid->points[i];
        float x = p->x;
        float y = p->y;
        p->x = x * c - y * s;
        p->y = x * s + y * c;
    }
}

void	project_perspective(t_point *p, float f, int screen_w, int screen_h, t_grid *grid)
{
	float	camera_z;
	float	relative_z;

	camera_z = 500.0f;
	relative_z = p->z - camera_z;
	if (relative_z > -1.0f)
		relative_z = -1.0f;
	p->x = (p->x * f) / relative_z + screen_w / 2 + grid->x + 100;
	p->y = (p->y * f) / relative_z + screen_h / 2 + grid->y;
}

void	project_isometric(t_point *p, t_grid *grid)
{
	int	x;
	int	y;
	
	x = p->x - p->y + WIDTH / 2;
	y = (p->x + p->y) / 2 - p->z + HEIGHT / 2;
	p->x = x + grid->x + 100;
	p->y = y + grid->y; 
}

void    reset_img(t_data *img)
{
        int     y;  
        int     x;  

        y = 0;
        while (y < HEIGHT)
        {
                x = 0;
                while (x < WIDTH)
			my_mlx_pixel_put(img, x++, y, 0x222221);
		y++;
        }
}

int	get_color(int i)
{
	if (i == 2 || i == 3)
		return (0xff7000);
	if (i == 1)
		return (0xff0000);
	if (i == 0)
		return (0xffffff);
}

void	obj_init(t_grid *grid)
{
	int	i;
	int	width;
	int	height;
	int	scale;

	i = 0;
	width = grid->width;
	height = grid->height;
	scale = 5;
	while (i < grid->size)
	{
		grid->points[i].x = (i % width - width / 2) * scale;
		grid->points[i].y = (i / width - height / 2) * scale;
		i++; 
	}
}

void draw_map(t_grid *grid, int edit_mode)
{
	int width = grid->width;
	int height = grid->height;
	int spacing = grid->z;
	float f = 600.0f;
	int i = 0;
	int j;
	int gx, gy;
	t_point a, b, c;

	reset_img(grid->img);
	grid->selected_points[grid->s_point] += 2;
	while (i < grid->size)
	{
		a = grid->points[i];
		printf("%f %f %f\n", a.x, a.y, a.z);
		if (edit_mode)
			a.color = get_color(grid->selected_points[i]);
		if (grid->view_mode == 1)
			project_perspective(&a, f, WIDTH, HEIGHT, grid);
		else if (grid->view_mode == 2)
			project_isometric(&a, grid);
		my_mlx_pixel_put(grid->img, a.x, a.y, a.color); 
		i++;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, grid->img->img, 0, 0);
	grid->selected_points[grid->s_point] -= 2;
}
