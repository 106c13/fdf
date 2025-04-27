/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:41:05 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/27 13:55:07 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(float c)
{
	if (c < 0)
		c *= -1;
	return ((int)c);
}

int	update_points(t_point *p0, t_point *p1, int a, char c)
{
	if (c == 'x')
	{
		if (p0->x < p1->x)
			p0->x++;
		else
			p0->x--;
	}
	else if (c == 'y')
	{
		if (p0->y < p1->y)
			p0->y++;
		else
			p0->y--;
	}
	return (a);
}

void	draw_line(t_point p0, t_point p1, t_data *img)
{
	int		dx;
	int		dy;
	int		err;
	float	i;
	float	n;

	dx = ft_abs(p1.x - p0.x);
	dy = ft_abs(p1.y - p0.y);
	err = dx - dy;
	i = 0;
	n = dx;
	if (dx < dy)
		n = dy;
	while (ft_abs(p0.x - p1.x) > 1 || ft_abs(p0.y - p1.y) > 1)
	{
		my_mlx_pixel_put(img, p0.x, p0.y,
			gradient(p0.color, p1.color, i / n));
		if (err > -dy)
			err -= update_points(&p0, &p1, dy, 'x');
		if (err < dx)
			err += update_points(&p0, &p1, dx, 'y');
		i++;
	}
}

void	draw_map(t_grid *grid, int edit_mode)
{
	int		i;
	t_point	a;
	t_point	b;

	i = 0;
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
		my_mlx_pixel_put(grid->img, a.x, a.y, a.color);
		i++;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, grid->img->img, 0, 0);
	grid->selected_points[grid->s_point] -= 2;
}
