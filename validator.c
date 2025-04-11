#include "fdf.h"

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

int	is_color(char **str)
{
	int	i;

	i = 0;
	(*str)++;
	if (**str != '0' || *(*str + 1) != 'x')
		return (0);
	*str += 2;
	while (i < 6)
	{
		if (!is_valid_symbol(*(*str + i), "0123456789ABCDEFabcdef"))
			return (0);
		i++;
	}
	*str += i;
	if (**str != ' ' && **str != '\n' && **str != '\0')
		return (0);
	return (1);
}

int	is_valid(char **str)
{
	long	num;
	int		sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	if (!is_valid_symbol(**str, "0123456789"))
		return (0);
	num = 0;
	while (**str && **str != ',' && **str != '\n' && **str != ' ')
	{
		if (!is_valid_symbol(**str, "0123456789"))
			return (0);
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	if (sign * num > INT_MAX || sign * num < INT_MIN)
		return (0);
	if (**str == ',')
		return (is_color(str));
	return (1);
}

int	count_words(char *str)
{
	int	count;
	int	first;

	count = 0;
	first = 1;
	while (*str && *str != '\n')
	{
		if (*str != ' ' && (first || *(str - 1) == ' '))
		{
			if (!is_valid(&str))
				return (-1);
			count++;
		}
		first = 0;
		str++;
	}
	return (count);
}

// TODO: Fix this function
int	get_grid_size(int fd)
{
	int		size;
	int		width;
	char	*line;

	if (read(fd, 0, 0) == -1)
		return (error("File not exists\n", -1));
	size = 0;
	width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (size == 0)
			width = count_words(line);
		else if (width != count_words(line))
			return (error("File is invalid\n", -1));
		if (width <= 0)
			return (error("File is invalid\n", -1));
		size += width;
		free(line);
		line = get_next_line(fd);
	}
	return (size);
}
