/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:08:01 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/08 16:28:27 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_strings(char *str, char sep)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str != sep && (*(str + 1) == sep || *(str + 1) == '\0'))
			count++;
		str++;
	}
	return (count);
}

char	*get_string(char *s, int start, int end)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((end - start + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[end - start] = '\0';
	while ((start + i) < end)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}

int	ft_fill_list(char *str, char sep, char **list)
{
	int	start;
	int	i;
	int	count;

	i = 0;
	start = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != sep)
		{
			if (i == 0 || str[i - 1] == sep)
				start = i;
			if (str[i + 1] == sep || str[i + 1] == '\0')
			{
				list[count] = get_string(str, start, i + 1);
				if (list[count] == NULL)
					return (0);
				count++;
			}
		}
		i++;
	}
	return (1);
}

void	ft_free_list(char **list)
{
	char **temp;

	temp = list;
	while (*list)
	{
		free(*list);
		list++;
	}
	free(temp);
}

char	**ft_split(char *str, char sep)
{
	char	**list;
	int		count;

	count = count_strings(str, sep);
	if (count == 0)
		return (NULL);
	list = malloc((count + 1) * sizeof(char *));
	if (list == NULL)
		return (NULL);
	if (!ft_fill_list(str, sep, list))
	{
		ft_free_list(list);
		return (NULL);
	}
	list[count] = 0;
	return (list);
}
