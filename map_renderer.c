#include "fdf.h"

void	draw_map(t_grid *grid, t_vars *vars)
{	
	t_data	img;
	int	i;
	int	j;
	int	s;
	int	x;
	int	y;
	int	gw;

	img.img = mlx_new_image(vars->mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	i = 0;
	gw = 500 / grid->width / 2;
	x = gw;
	y = gw;
	while (i < grid->size)
	{
		my_mlx_pixel_put(&img, x, y, grid->colors[i]);
		j = 1;
		while (j < gw)
		{
			if ((i + 1) % grid->width != 0)	
				my_mlx_pixel_put(&img, x + j, y, grid->colors[i]);
			if (i % grid->width != grid->height)
				my_mlx_pixel_put(&img, x, y + j, grid->colors[i]);
			j++;
		}
		x += gw;
		i++;
		if (i % grid->width == 0)
		{
			x = gw;
			y += gw;
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
}
