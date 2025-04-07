/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:46:37 by haaghaja          #+#    #+#             */
/*   Updated: 2025/02/20 14:31:40 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_calloc(ssize_t size)
{
	char	*str;

	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

char	*get_next_line(int fd)
{
	char		*str;
	ssize_t		bytes_read;
	static char	*buffer[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	if (buffer[fd] == NULL)
		buffer[fd] = ft_calloc(BUFFER_SIZE);
	if (!buffer[fd])
		return (NULL);
	while (!ft_get_line(&str, buffer[fd]))
	{
		bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read == -1)
			return (exit_gnl(str, &buffer[fd]));
		buffer[fd][bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
	}
	if (str == NULL || *str == '\0')
		return (exit_gnl(str, &buffer[fd]));
	shift_buffer(buffer[fd]);
	return (str);
}
