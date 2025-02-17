/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:43:56 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/13 01:21:36 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moove_fw_bw(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	all->sprint = false;
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT_SHIFT)
		&& mlx_is_key_down(all->mlx, MLX_KEY_W))
	{
		all->sprint = true;
		move_forward(all);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_W))
		move_forward(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT_SHIFT)
		&& mlx_is_key_down(all->mlx, MLX_KEY_S))
	{
		all->sprint = true;
		move_backward(all);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		move_backward(all);
	draw_fov(all);
}

void	moove_left_right(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	all->sprint = false;
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT_SHIFT)
		&& mlx_is_key_down(all->mlx, MLX_KEY_D))
	{
		all->sprint = true;
		move_left(all);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		move_left(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT_SHIFT)
		&& mlx_is_key_down(all->mlx, MLX_KEY_A))
	{
		all->sprint = true;
		move_right(all);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		move_right(all);
}

void	init_player(t_all **all, int i, int j)
{
	(*all)->player_pos.x = (j + 0.5) * TILE_SIZE;
	(*all)->player_pos.y = (i + 0.5) * TILE_SIZE;
	(*all)->starting_dir = (*all)->map[i][j];
	if ((*all)->map[i][j] == 'N')
		(*all)->player_angle = 3 * M_PI / 2;
	else if ((*all)->map[i][j] == 'E')
		(*all)->player_angle = 0;
	else if ((*all)->map[i][j] == 'S')
		(*all)->player_angle = M_PI / 2;
	else if ((*all)->map[i][j] == 'W')
		(*all)->player_angle = M_PI;
	(*all)->map[i][j] = '0';
}
