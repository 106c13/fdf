/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:53:22 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/12 15:01:53 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_line(char *line, t_grid *grid, int *i)
{
	int	num;
	int	sign;
	int	width;

	width = 0;
	while (*line && *line != '\n')
	{
		num = 0;
		sign = 1;
		if (*line != ' ')
		{
			if (*line == '-')
			{
				sign = -1;
				line++;
			}
			while (*line >= '0' && *line <= '9')
			{
				num = num * 10 + *line - 48;
				line++;
			}
			grid->values[*i] = num * sign;
			if (*line == ',')
				grid->colors[*i] = ft_htod(&line);
			else
				grid->colors[*i] = 16777215;
			(*i)++;
			width++;
		}
		line++;
	}
	grid->width = width;
}

void	parse_file(int fd, t_grid *grid)
{
	char	*line;
	int	height;
	int	i;

	line = get_next_line(fd);
	height = 0;
	i = 0;
	while (line)
	{
		height++;
		parse_line(line, grid, &i);
		free(line);
		line = get_next_line(fd);
	}
	grid->height = height;
}

int	create_grid(char *fname, t_grid *grid)
{
	int		size;
	int		fd;

	fd = open(fname, O_RDONLY);
	size = get_grid_size(fd);
	close(fd);
	if (size < 1)
		return (0);
	grid->values = (int *)malloc(sizeof(int) * size);
	grid->colors = (int *)malloc(sizeof(int) * size);
	if (!grid->values || !grid->colors)
		return (error("Can't allocate memory\n", 0));
	fd = open(fname, O_RDONLY);
	parse_file(fd, grid);
	grid->size = size;
	return (1);
}
