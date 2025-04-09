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

int	error(char *msg, int out)
{
	while (*msg)
		write(1, msg++, 1);
	return (out);
}

int	is_valid_symbol(char c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}									

int	count_words(char *str)
{
	int	count;

	count = 0;
	while (*str && *str != '\n')
	{
		if (!is_valid_symbol(*str, "0123456789xABCDEFabcdef,- "))
			return (-1);
		if (*str != ' ' && (*(str + 1) == ' ' || *(str + 1) == '\0'))
			count++;
		str++;
	}
	return (count);
}

// TODO: Fix this function
int	count_size(int fd)
{
	int	size;
	int	height;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	height = count_words(line);
	if (height == -1)
		return (-1);
	size = height;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (height != count_words(line))
			return (error("Heights aren't equal\n", -1));
		size += height;
	}
	return (size);
}
			

	
	


void	parse_line(char *line)
{
	char	**points;
	//t_grin	point;

	points = ft_split(line, ' ');
	while (*points)
	{
		ft_printf("%s ", *points);
		points++;
	}
}
/*
t_grid	*parse_file(int fd)
{
	char	*line;	

	ft_printf(" ");	
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line);
		free(line);
		line = get_next_line(fd);
	}
	return (grid);
}
*/
int	main(int argc, char **argv)
{
	int	fd;
	//t_grid	*grid;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (error("File not exists\n", 0));
		ft_printf("%d\n", count_size(fd));
		//parse_file(fd);
		//if (!grid)
		//	return (0);
	}
	return (0);
}
