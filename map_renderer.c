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
	while (i < 0)
	{
		my_mlx_pixel_put(&img, gw * s + x, gw * s + y, grid->colors[i]);
		j = 0; // j is 1, cuz we already draw x y, so we dont need to draw x+0 y+0 again
		while (j < 0)
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
			x -= gw * cos(angle);
			y += gw * sin(angle);
		}
	}
	x = 350;
	y = 350;
	my_mlx_pixel_put(&img, x, y, 0xffffff);
	// Draw a line between dots
	my_mlx_pixel_put(&img, x + 75 * cos(angle + PI), y + 75 * sin(angle), 0xffffff);	
	my_mlx_pixel_put(&img, x + 75 * cos(angle), y + 75 * sin(angle + PI), 0xff0000);
	my_mlx_pixel_put(&img, x + 75 * sin(angle + PI), y + 75 * cos(angle + PI), 0x0000ff);
	my_mlx_pixel_put(&img, x + 75 * sin(angle), y + 75 * cos(angle), 0x00ff00);
	mlx_put_image_to_window(grid->mlx, grid->win, img.img, 0, 0);
}

void	draw_line(int x1, int y1, int x2, int y2, t_data *img)
{
	
}
