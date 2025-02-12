/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:14:59 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/12 15:18:02 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_all *all)
{
	all->player_angle += ROT_SPEED;
	if (all->player_angle > 2 * M_PI) // Empêcher un dépassement d'angle
		all->player_angle -= 2 * M_PI;
}

void	rotate_left(t_all *all)
{
	all->player_angle -= ROT_SPEED;
	if (all->player_angle < 0)
		all->player_angle += 2 * M_PI;
}

void	fov_mooves(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
		rotate_right(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		rotate_left(all);
}
