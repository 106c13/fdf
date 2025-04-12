/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:16 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/12 15:30:22 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"



int	main(int argc, char **argv)
{
	t_grid	*grid;
	void	*mlx;
	void	*mlx_window;

	if (argc == 2)
	{
		grid = create_grid(argv[1]);
		if (grid)
			ft_printf("%d %x\n", grid->height, grid->color);
		mlx = mlx_init();
		mlx_window = mlx_new_window(mlx, 400, 400, "Seigh Heil!");
		mlx_loop(mlx);
	}
	return (0);
}
