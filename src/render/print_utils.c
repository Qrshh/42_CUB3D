/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:12:46 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/10 21:28:21 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	square(t_all *all, int x, int y, int color)
{
	int	i;
	int	j;
	mlx_image_t	*square;

	i = 0;
	square = mlx_new_image(all->mlx, TILE_SIZE, TILE_SIZE);
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(square, i, j, color);
			j++;
		}
		i++;
	}
	if (mlx_image_to_window(all->mlx, square, x, y) < 0)
		ft_all_exit(all, "mlx_image_to_window failed in square");
}

void	draw_map(t_all *all)
{
	int	i = 0;
	int	j = 0;

	while (all->map && all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				square(all, j * TILE_SIZE, i * TILE_SIZE, 0xECCBD9);
			else if (all->map[i][j] == '0')
				square(all, j * TILE_SIZE, i * TILE_SIZE, 0x97D2FB);
			j++;
		}
		i++;
	}
}
