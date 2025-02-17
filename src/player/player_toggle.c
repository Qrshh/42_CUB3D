/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_toggle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:04:12 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/17 20:28:08 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_mouse_fov(t_all *all)
{
	all->fov_mouse = !all->fov_mouse;
	if (all->fov_mouse)
	{
		mlx_set_cursor_mode(all->mlx, MLX_MOUSE_DISABLED);
		mlx_cursor_hook(all->mlx, mouse_moove, all);
	}
	else
		mlx_set_cursor_mode(all->mlx, MLX_MOUSE_NORMAL);
}

void	toggle_minimap(t_all *all)
{
	all->minimap_visible = !all->minimap_visible;
	if (!all->minimap_visible && all->minimap_img)
	{
		mlx_delete_image(all->mlx, all->minimap_img);
		all->minimap_img = NULL;
	}
}

int is_near_door(t_all *all)
{
    double next_x = all->player_pos.x;
    double next_y = all->player_pos.y;
    int map_x, map_y;

    next_x += cos(all->player_angle) * TILE_SIZE; 
    next_y += sin(all->player_angle) * TILE_SIZE;

    map_x = (int)(next_x / TILE_SIZE);
    map_y = (int)(next_y / TILE_SIZE);
    if (all->map[map_y][map_x] == 'D')
        return 1;
	else if (all->map[map_y][map_x] == '6')
		return (2);
    
    return 0;
}
void toggle_door(t_all *all)
{
    double next_x = all->player_pos.x;
    double next_y = all->player_pos.y;
    int map_x, map_y;

    if (is_near_door(all) == 1)
    {
        next_x += cos(all->player_angle) * TILE_SIZE;
        next_y += sin(all->player_angle) * TILE_SIZE;
        map_x = (int)(next_x / TILE_SIZE);
        map_y = (int)(next_y / TILE_SIZE);
        all->map[map_y][map_x] = '6';
    }
	else if (is_near_door(all) == 2)
	{
		next_x += cos(all->player_angle) * TILE_SIZE;
        next_y += sin(all->player_angle) * TILE_SIZE;
        map_x = (int)(next_x / TILE_SIZE);
        map_y = (int)(next_y / TILE_SIZE);
        all->map[map_y][map_x] = 'D';
	}
}


void	toggle(mlx_key_data_t keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_RELEASE)
		toggle_minimap(all);
	else if (keydata.key == MLX_KEY_P && keydata.action == MLX_RELEASE)
		toggle_mouse_fov(all);
	else if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
		toggle_door(all);
}
