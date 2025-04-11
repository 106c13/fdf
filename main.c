/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:16 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/08 17:54:10 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_htod(char **str)
{
	int	num;

	num = 0;
	(*str) += 3;
	while (**str && **str != ' ' && **str != '\n')
	{
		if (**str >= '0' && **str <= '9')
			num = num * 16 + **str - '0';
		else if (**str >= 'a' && **str <= 'f')
			num = num * 16 + **str - 'a' + 10;
		else if (**str >= 'A' && **str <= 'F')
			num = num * 16 + **str - 'A' + 10;
		(*str)++;
	}
	return (num);
}

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
	int	size;
	int	fd;
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


int	main(int argc, char **argv)
{
	t_grid	*grid;

	if (argc == 2)
	{
		grid = create_grid(argv[1]);
		if (grid)
			ft_printf("%d %x\n", grid->height, grid->color);
	}
	return (0);
}
