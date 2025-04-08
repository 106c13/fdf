/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:07:55 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/08 17:51:41 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"
// TODO: remove this V
#include "ft_printf.h"

typedef struct s_grid
{
	int	height;
	int	color;
	char	end;
	struct s_grid	*next;
} t_grid;

char	**ft_split(char *str, char sep);


#endif
