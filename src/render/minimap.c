/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:24:23 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/19 23:44:52 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_color(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (map[y][x] == '1')
		return (0x0D4B00FF);
	else if (map[y][x] == 'D')
		return (0x824B0CFF);
	else if (map[y][x] == '0')
		return (0x25D500FF);
	else if (map[y][x] == '6')
		return (0x1DA900FF);
	return (0);
}

void	browse_map(t_all *all)
{
	int	map_x;
	int	map_y;
	int	i;
	int	j;

	map_y = -1;
	while (all->map[++map_y])
	{
		map_x = -1;
		while (all->map[map_y][++map_x])
		{
			i = -1;
			while (++i < 10)
			{
				j = -1;
				while (++j < 10)
				{
					mlx_put_pixel(all->minimap_img, 10 + map_x * 10 + i, 10
						+ map_y * 10 + j, get_color(all->map, map_x, map_y));
				}
			}
		}
	}
}

void	draw_minimap(t_all *all)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	if (!all || !all->minimap_visible)
		return ;
	if (!all->minimap_img)
		all->minimap_img = mlx_new_image(all->mlx, 1000, 1000);
	browse_map(all);
	player_x = 10 + (all->player_pos.x / TILE_SIZE) * 10;
	player_y = 10 + (all->player_pos.y / TILE_SIZE) * 10;
	i = 0;
	while (i < 10 / 2)
	{
		j = 0;
		while (j < 10 / 2)
		{
			mlx_put_pixel(all->minimap_img, player_x + i, player_y + j,
				0xFFFFFFFF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(all->mlx, all->minimap_img, 10, 10);
}
