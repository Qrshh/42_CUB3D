/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mooves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:10:58 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/17 20:09:09 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	if (all->sprint)
	{
		next_x = all->player_pos.x + cos(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
		next_y = all->player_pos.y + sin(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
	}
	else
	{
		next_x = all->player_pos.x + cos(all->player_angle) * MOV_SPEED;
		next_y = all->player_pos.y + sin(all->player_angle) * MOV_SPEED;
	}
	map_x = (int)((next_x + COLLISION_MARGIN * cos(all->player_angle))
			/ TILE_SIZE);
	map_y = (int)((next_y + COLLISION_MARGIN * sin(all->player_angle))
			/ TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0')
		all->player_pos.x = next_x;
}

void	move_backward(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	if (all->sprint)
	{
		next_x = all->player_pos.x - cos(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
		next_y = all->player_pos.y - sin(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
	}
	else
	{
		next_x = all->player_pos.x - cos(all->player_angle) * MOV_SPEED;
		next_y = all->player_pos.y - sin(all->player_angle) * MOV_SPEED;
	}
	map_x = (int)((next_x - COLLISION_MARGIN * cos(all->player_angle))
			/ TILE_SIZE);
	map_y = (int)((next_y - COLLISION_MARGIN * sin(all->player_angle))
			/ TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0')
		all->player_pos.x = next_x;
}

void	move_left(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	if (all->sprint)
	{
		next_x = all->player_pos.x - sin(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
		next_y = all->player_pos.y + cos(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
	}
	else
	{
		next_x = all->player_pos.x - sin(all->player_angle) * MOV_SPEED;
		next_y = all->player_pos.y + cos(all->player_angle) * MOV_SPEED;
	}
	map_x = (int)((next_x - COLLISION_MARGIN * sin(all->player_angle))
			/ TILE_SIZE);
	map_y = (int)((next_y + COLLISION_MARGIN * cos(all->player_angle))
			/ TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0')
		all->player_pos.x = next_x;
}

void	move_right(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	if (all->sprint)
	{
		next_x = all->player_pos.x + sin(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
		next_y = all->player_pos.y - cos(all->player_angle) * MOV_SPEED
			* BIG_SPEED;
	}
	else
	{
		next_x = all->player_pos.x + sin(all->player_angle) * MOV_SPEED;
		next_y = all->player_pos.y - cos(all->player_angle) * MOV_SPEED;
	}
	map_x = (int)((next_x + COLLISION_MARGIN * sin(all->player_angle))
			/ TILE_SIZE);
	map_y = (int)((next_y - COLLISION_MARGIN * cos(all->player_angle))
			/ TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0')
		all->player_pos.x = next_x;
}
