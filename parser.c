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

t_grid	*parse_line(char *line, t_grid *grid)
{
	int	num;
	int	sign;
	int	i;

	i = 0;
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
			grid[i].height = num * sign;
			if (*line == ',')
				grid[i].color = ft_htod(&line);
			else
				grid[i].color = 16777215;
			if (i > 0)
				grid[i - 1].next = &grid[i];
			i++;
		}
		line++;
	}
	grid[i - 1].next = &grid[i];
	return (&grid[i]);
}

void	parse_file(int fd, t_grid *grid)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		grid = parse_line(line, grid);
		free(line);
		line = get_next_line(fd);
	}
	(*(grid - 1)).next = NULL;
}

t_grid	*create_grid(char *fname)
{
	int		size;
	int		fd;
	t_grid	*grid;

	fd = open(fname, O_RDONLY);
	size = get_grid_size(fd);
	ft_printf("SIZE: %d\n", size);
	close(fd);
	if (size < 1)
		return (NULL);
	grid = malloc(sizeof(t_grid) * size);
	if (!grid)
		return (error_ptr("Can't allocate memory\n", NULL));
	fd = open(fname, O_RDONLY);
	parse_file(fd, grid);
	return (grid);
}
