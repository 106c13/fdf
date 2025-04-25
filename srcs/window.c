#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
	{
		dst = data->addr + (y * data->l + x * (data->b / 8));
		*(int *)dst = color;
	}
}

void	draw_background(t_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH / 7)
		{
			my_mlx_pixel_put(img, x, y, 0x37383b);
			x++;
		}
		y++;
	}
}

void	put_text(t_grid *grid, int y, int color, char *str)
{
	mlx_string_put(grid->mlx, grid->win, 40, y, color, str);
}

void	draw_menu(t_grid *grid)
{
	draw_background(grid->img);
	put_text(grid, 20, 0xFFFFFF, "Menu");
	put_text(grid, 60, 0xe5e5df, "X: Left/Right");
	put_text(grid, 80, 0xe5e5df, "Y: Up/Down");
	put_text(grid, 120, 0xe5e5df, "X angle: W S");
	put_text(grid, 140, 0xe5e5df, "Y angle: Q E");
	put_text(grid, 160, 0xe5e5df, "Z angle: A D");
	put_text(grid, 200, 0xe5e5df, "Zoom in/out: Space/Tab");
	put_text(grid, 240, 0xe5e5df, "Perspective: 1");
	put_text(grid, 260, 0xe5e5df, "Isometric: 2");
	put_text(grid, 320, 0xe5e5df, "Editor Mode");
	put_text(grid, 340, 0xe5e5df, "Enter/Exit: V");
	put_text(grid, 360, 0xe5e5df, "Select point: C");
	put_text(grid, 380, 0xe5e5df, "Deselect point: C");
	put_text(grid, 400, 0xe5e5df, "Deselect all: X");
	put_text(grid, 420, 0xe5e5df, "Increase height: +");
	put_text(grid, 440, 0xe5e5df, "Decrease height: -");
	put_text(grid, 490, 0xe5e5df, "Move Left: J");
	put_text(grid, 510, 0xe5e5df, "Move Right: L");
	put_text(grid, 530, 0xe5e5df, "Move Up: I");
	put_text(grid, 550, 0xe5e5df, "Move Down: K");
}

void	change_height(t_grid *grid, int value)
{
	int	i;

	i = 0;
	while (i < grid->size)
	{
		if (grid->selected_points[i] != 0)
			grid->points[i].z += value;
		i++;
	}
}
