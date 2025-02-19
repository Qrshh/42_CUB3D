/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mooves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:10:58 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/19 23:55:52 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	if (!all->sprint)
	{
		next_x = all->player_pos.x + cos(all->player_angle) * MOV_SPEED;
		next_y = all->player_pos.y + sin(all->player_angle) * MOV_SPEED;
	}
	else
	{
		next_x = all->player_pos.x + cos(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
		next_y = all->player_pos.y + sin(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
	}
	map_x = (int)((next_x + COLL_MARG * cos(all->player_angle)) / TILE_SIZE);
	map_y = (int)((next_y + COLL_MARG * sin(all->player_angle)) / TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0'
		|| all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '6')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0'
		|| all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '6')
		all->player_pos.x = next_x;
}

void	move_backward(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	next_x = all->player_pos.x - cos(all->player_angle) * MOV_SPEED;
	next_y = all->player_pos.y - sin(all->player_angle) * MOV_SPEED;
	if (all->sprint)
	{
		next_x = next_x * BIG_SPEED;
		next_y = next_y * BIG_SPEED;
	}
	map_x = (int)((next_x - COLL_MARG * cos(all->player_angle)) / TILE_SIZE);
	map_y = (int)((next_y - COLL_MARG * sin(all->player_angle)) / TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0'
		|| all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '6')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0'
		|| all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '6')
		all->player_pos.x = next_x;
}

void	move_left(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	next_x = all->player_pos.x - sin(all->player_angle) * MOV_SPEED;
	next_y = all->player_pos.y + cos(all->player_angle) * MOV_SPEED;
	if (all->sprint)
	{
		next_x = next_x * BIG_SPEED;
		next_y = next_y * BIG_SPEED;
	}
	map_x = (int)((next_x - COLL_MARG * sin(all->player_angle)) / TILE_SIZE);
	map_y = (int)((next_y + COLL_MARG * cos(all->player_angle)) / TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0'
		|| all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '6')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0'
		|| all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '6')
		all->player_pos.x = next_x;
}

void	move_right(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	next_x = all->player_pos.x + sin(all->player_angle) * MOV_SPEED;
	next_y = all->player_pos.y - cos(all->player_angle) * MOV_SPEED;
	if (all->sprint)
	{
		next_x = next_x * BIG_SPEED;
		next_y = next_y * BIG_SPEED;
	}
	map_x = (int)((next_x + COLL_MARG * sin(all->player_angle)) / TILE_SIZE);
	map_y = (int)((next_y - COLL_MARG * cos(all->player_angle)) / TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0'
		|| all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '6')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0'
		|| all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '6')
		all->player_pos.x = next_x;
}
