/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:07:55 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/12 14:57:25 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
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


// ft_splic.c
char	**ft_split(char *str, char sep);

// validator.c
int	get_grid_size(int fd);

// parser.c
t_grid	*create_grid(char *fname);

// utils.c
int	ft_htod(char **str);

// main.c
int	error(char *str, int out);

// error_handlers.c
void	*error_ptr(char *msg, void *ptr);
int	error(char *msg, int error_code);

#endif
