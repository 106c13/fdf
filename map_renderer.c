#include "fdf.h"
#include <stdio.h>

void	draw_map(t_grid *grid, double angle)
{
	t_data	img;
	int	i;
	int	j;
	int	s;
	int	x;
	int	y;
	int	gw;

	img.img = mlx_new_image(grid->mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	i = 0;
	gw = 500 / grid->width / 2;
	x = 300;
	y = 100;
	s = 0;
	printf("%f %f\n", sin(angle), cos(angle));
	//my_mlx_pixel_put(&img, 0, 0, 0xffff00);
	while (i < grid->size)
	{
		my_mlx_pixel_put(&img, gw * s + x, gw * s + y, grid->colors[i]);
		j = 0; // j is 1, cuz we already draw x y, so we dont need to draw x+0 y+0 again
		while (j < gw)
		{
			if ((i + 1) % grid->width != 0)	
				my_mlx_pixel_put(&img, gw * s + x + j * cos(angle), gw * s + y + sin(angle) * j, grid->colors[i]);
			if ((i / grid->width + 1) != grid->height)
				my_mlx_pixel_put(&img, gw * s + x - j * sin(angle), gw * s + y + j * cos(angle), grid->colors[i]);	
			j++;
		}
		s++;
		i++;
		if (i % grid->width == 0)
		{
			s = 0;
			x -= gw;
			y += gw;
		}
	}
	mlx_put_image_to_window(grid->mlx, grid->win, img.img, 0, 0);
}
