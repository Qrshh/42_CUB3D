/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:10:58 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/11 20:01:11 by mosmont          ###   ########.fr       */
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

void rotate_right(t_all *all)
{
    all->player_angle += ROT_SPEED;
    if (all->player_angle > 2 * M_PI) // Empêcher un dépassement d'angle
        all->player_angle -= 2 * M_PI;
}

void rotate_left(t_all *all)
{
    all->player_angle -= ROT_SPEED;
    if (all->player_angle < 0)
        all->player_angle += 2 * M_PI;
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
	draw_fov(all); // Si ca lag trop faut bouger ca dans les touches
}

void	fov_mooves(void *param)
{
	t_all *all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
		rotate_right(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		rotate_left(all);
}