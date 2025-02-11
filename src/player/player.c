/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:10:58 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/11 19:15:04 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	up(t_all *all)
{
	int	next_i;
	int	j;

	next_i = (all->player_pos.y - MOV_SPEED) / TILE_SIZE;
	j = all->player_pos.x / TILE_SIZE;
	if (all->map[next_i][j] != '1')
	{
		all->player_pos.y -= MOV_SPEED;
		all->img->instances[0].y -= MOV_SPEED;
		printf("%f : %f\n", all->player_pos.x / TILE_SIZE, all->player_pos.y
			/ TILE_SIZE);
	}
}

void	down(t_all *all)
{
	int	next_i;
	int	j;

	next_i = (all->player_pos.y + MOV_SPEED) / TILE_SIZE;
	j = all->player_pos.x / TILE_SIZE;
	if (all->map[next_i][j] != '1')
	{
		all->player_pos.y += MOV_SPEED;
		all->img->instances[0].y += MOV_SPEED;
		printf("%f : %f\n", all->player_pos.x / TILE_SIZE, all->player_pos.y
			/ TILE_SIZE);
	}
}

void	left(t_all *all)
{
	int	i;
	int	next_j;

	i = all->player_pos.y / TILE_SIZE;
	next_j = (all->player_pos.x + MOV_SPEED) / TILE_SIZE;
	if (all->map[i][next_j] != '1')
	{
		all->player_pos.x += MOV_SPEED;
		all->img->instances[0].x += MOV_SPEED;
		printf("%f : %f\n", all->player_pos.x / TILE_SIZE, all->player_pos.y
			/ TILE_SIZE);
	}
}

void	right(t_all *all)
{
	int	i;
	int	next_j;

	i = all->player_pos.y / TILE_SIZE;
	next_j = (all->player_pos.x - MOV_SPEED) / TILE_SIZE;
	if (all->map[i][next_j] != '1')
	{
		all->player_pos.x -= MOV_SPEED;
		all->img->instances[0].x -= MOV_SPEED;
		printf("%f : %f\n", all->player_pos.x / TILE_SIZE, all->player_pos.y
			/ TILE_SIZE);
	}
}

void	event_listener(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_W))
		up(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		down(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		left(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		right(all);
	clear_ray(all);
	draw_ray(all, M_PI / 8);
}
