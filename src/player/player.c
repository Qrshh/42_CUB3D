/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:10:58 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/11 21:52:34 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_forward(t_all *all)
{
    double next_x = all->player_pos.x - cos(all->player_angle) * MOV_SPEED;
    double next_y = all->player_pos.y - sin(all->player_angle) * MOV_SPEED;
    int map_x = (int)((next_x - COLLISION_MARGIN * cos(all->player_angle)) / TILE_SIZE);
    int map_y = (int)((next_y - COLLISION_MARGIN * sin(all->player_angle)) / TILE_SIZE);

    if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] != '1')
        all->player_pos.y = next_y;
    if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] != '1')
        all->player_pos.x = next_x;

    all->img->instances[0].x = all->player_pos.x;
    all->img->instances[0].y = all->player_pos.y;
}

void move_backward(t_all *all)
{
	double next_x = all->player_pos.x + cos(all->player_angle) * MOV_SPEED;
    double next_y = all->player_pos.y + sin(all->player_angle) * MOV_SPEED;
    int map_x = (int)((next_x + COLLISION_MARGIN * cos(all->player_angle)) / TILE_SIZE);
    int map_y = (int)((next_y + COLLISION_MARGIN * sin(all->player_angle)) / TILE_SIZE);

    if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] != '1')
        all->player_pos.y = next_y;
    if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] != '1')
        all->player_pos.x = next_x;

    all->img->instances[0].x = all->player_pos.x;
    all->img->instances[0].y = all->player_pos.y;
}

void move_left(t_all *all)
{
    double next_x = all->player_pos.x - sin(all->player_angle) * MOV_SPEED;
    double next_y = all->player_pos.y + cos(all->player_angle) * MOV_SPEED;
    int map_x = (int)((next_x - COLLISION_MARGIN * sin(all->player_angle)) / TILE_SIZE);
    int map_y = (int)((next_y + COLLISION_MARGIN * cos(all->player_angle)) / TILE_SIZE);

    if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] != '1')
        all->player_pos.y = next_y;
    if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] != '1')
        all->player_pos.x = next_x;

    all->img->instances[0].x = all->player_pos.x;
    all->img->instances[0].y = all->player_pos.y;
}

void move_right(t_all *all)
{
    double next_x = all->player_pos.x + sin(all->player_angle) * MOV_SPEED;
    double next_y = all->player_pos.y - cos(all->player_angle) * MOV_SPEED;
    int map_x = (int)((next_x + COLLISION_MARGIN * sin(all->player_angle)) / TILE_SIZE);
    int map_y = (int)((next_y - COLLISION_MARGIN * cos(all->player_angle)) / TILE_SIZE);

    if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] != '1')
        all->player_pos.y = next_y;
    if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] != '1')
        all->player_pos.x = next_x;

    all->img->instances[0].x = all->player_pos.x;
    all->img->instances[0].y = all->player_pos.y;
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
		move_forward(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		move_backward(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		move_left(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		move_right(all);
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