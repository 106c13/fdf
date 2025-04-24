#include "fdf.h"

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

void rotate_point(t_point *p, t_grid *grid)
{
    float x = p->x;
    float y = p->y;
    float z = p->z;

    float x1 = x;
    float y1 = y * cos(grid->x_angle) - z * sin(grid->x_angle);
    float z1 = y * sin(grid->x_angle) + z * cos(grid->x_angle);

    // Rotate around Y
    float x2 = x1 * cos(grid->y_angle) + z1 * sin(grid->y_angle);
    float y2 = y1;
    float z2 = -x1 * sin(grid->y_angle) + z1 * cos(grid->y_angle);

    // Rotate around Z
    float x3 = x2 * cos(grid->z_angle) - y2 * sin(grid->z_angle);
    float y3 = x2 * sin(grid->z_angle) + y2 * cos(grid->z_angle);
    float z3 = z2;
    p->x = x3;
    p->y = y3;
    p->z = z3;
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
		gx = i % width;
		gy = i / width;
		a.x = (gx - width / 2) * spacing * 2;
		a.y = (gy - height / 2) * spacing * 2;
		a.z = grid->values[i] * spacing;
		if (edit_mode)
			a.color = get_color(grid->selected_points[i]);
		else
			a.color = grid->colors[i];
		if (grid->values[i] != 0)
		    a.z += grid->h_scale;
		rotate_point(&a, grid);
			c.color = grid->colors[i + width];
		if (grid->view_mode == 1)
			project_perspective(&a, f, WIDTH, HEIGHT, grid);
		else if (grid->view_mode == 2)
			project_isometric(&a, grid); 
		if (gx < width - 1)
		{
			j = i + 1;
			b.x = ((j % width) - width / 2) * spacing * 2;
			b.y = ((j / width) - height / 2) * spacing * 2;
			b.z = grid->values[j] * spacing;
			if (edit_mode)
				b.color = get_color(grid->selected_points[i + 1]);
			else
				b.color = grid->colors[i + 1];
			if (grid->values[j] != 0)
				b.z += grid->h_scale;
			rotate_point(&b, grid);
			if (grid->view_mode == 1)
				project_perspective(&b, f, WIDTH, HEIGHT, grid);
			else if (grid->view_mode == 2)
				project_isometric(&b, grid); 
			draw_line(a, b, grid->img);
		}
		if (gy < height - 1)
		{
			j = i + width;
			c.x = ((j % width) - width / 2) * spacing * 2;
			c.y = ((j / width) - height / 2) * spacing * 2;
			c.z = grid->values[j] * spacing;
			if (edit_mode)
				c.color = get_color(grid->selected_points[i + width]);
			else
				c.color = grid->colors[i + width];
			if (grid->values[j] != 0)
				c.z += grid->h_scale;
			rotate_point(&c, grid);
			if (grid->view_mode == 1)
				project_perspective(&c, f, WIDTH, HEIGHT, grid);
			else if (grid->view_mode == 2)
				project_isometric(&c, grid); 
			draw_line(a, c, grid->img);
		}
		i++;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, grid->img->img, 0, 0);
	grid->selected_points[grid->s_point] -= 2;
}
