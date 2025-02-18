/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:24:23 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/18 04:00:35 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_all *all)
{
	int	offset_y;
	int	color;
	int	player_x;
	int	player_y;

	if (!all->minimap_visible)
		return ;
	int map_x, map_y;
	int tile_size = 10;
	int offset_x = 10;
	offset_y = 10;
	if (!all->minimap_img)
		all->minimap_img = mlx_new_image(all->mlx, 1000, 1000);
	for (map_y = 0; all->map[map_y]; map_y++)
	{
		for (map_x = 0; all->map[map_y][map_x]; map_x++)
		{
			color = (all->map[map_y][map_x] == '1') ? 0xFFFFFF : 0x00FF3A;
			for (int i = 0; i < tile_size; i++)
			{
				for (int j = 0; j < tile_size; j++)
				{
					mlx_put_pixel(all->minimap_img, offset_x + map_x * tile_size
						+ i, offset_y + map_y * tile_size + j, color);
				}
			}
		}
	}
	player_x = offset_x + (all->player_pos.x / TILE_SIZE) * tile_size;
	player_y = offset_y + (all->player_pos.y / TILE_SIZE) * tile_size;
	mlx_image_to_window(all->mlx, all->player_img, player_x, player_y);
	mlx_image_to_window(all->mlx, all->minimap_img, 10, 10);
}

