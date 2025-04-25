#include "fdf.h"

void	draw_line(t_point p0, t_point p1, t_data *img)
{
	int		dx;
	int		dy;
	int		err;
	float	i;
	float	n;

	dx = abs(p1.x - p0.x);
	dy = abs(p1.y - p0.y);
	err = dx - dy;
	i = 0;
	n = abs(p1.x - p0.x);
	if (n < abs(p1.y - p0.y))
		n = abs(p1.y - p0.y);
	while (abs(p0.x - p1.x) > 0 || abs(p0.y - p1.y) > 0)
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

t_point create_point(t_grid *grid, int i, int edit_mode)
{
        t_point p;

        p = grid->points[i];
        p.x *= grid->zoom;
        p.y *= grid->zoom;
        p.z *= grid->zoom;
        p.color = grid->points[i].color;
        if (edit_mode)
                p.color = get_color(grid->selected_points[i]);
        if (grid->view_mode == 1)
                project_perspective(&p, 600.0f, grid);
        else if (grid->view_mode == 2)
                project_isometric(&p, grid);
        return (p);
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
	int i = 0;
	t_point a, b;

	reset_img(grid->img);
	grid->selected_points[grid->s_point] += 2;
	while (i < grid->size)
	{
		a = create_point(grid, i, edit_mode);
		if (i % grid->width < grid->width - 1)
		{
			b = create_point(grid, i + 1, edit_mode);
			draw_line(a, b, grid->img);
		}
		if (i / grid->width < grid->height - 1)
		{
			b = create_point(grid, i + grid->width, edit_mode);
			draw_line(a, b, grid->img);
		}
		i++;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, grid->img->img, 0, 0);
	grid->selected_points[grid->s_point] -= 2;
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
