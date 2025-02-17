/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:14:59 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/12 21:05:16 by abesneux         ###   ########.fr       */
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
	if (all->fov_mouse)
		return ;
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
		rotate_right(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		rotate_left(all);
}

void	mouse_moove(double x_pos, double y_pos, void *param)
{
	t_all	*all;
	int		last_x;
	int		delta_x;

	(void)y_pos;
	all = (t_all *)param;
	if (!all->fov_mouse)
		return ;
	last_x = WIDTH / 2;
	delta_x = x_pos - last_x;
	all->player_angle += delta_x * SENS;
	if (all->player_angle > 2 * M_PI)
		all->player_angle -= 2 * M_PI;
	else if (all->player_angle < 0)
		all->player_angle += 2 * M_PI;
	mlx_set_mouse_pos(all->mlx, WIDTH / 2, HEIGHT / 2);
	last_x = WIDTH / 2;
}

void	toggle_mouse(mlx_key_data_t keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_RELEASE)
	{
		all->fov_mouse = !all->fov_mouse;
		if (all->fov_mouse)
		{
			mlx_set_cursor_mode(all->mlx, MLX_MOUSE_DISABLED);
			mlx_cursor_hook(all->mlx, mouse_moove, all);
		}
		else
		{
			mlx_set_cursor_mode(all->mlx, MLX_MOUSE_NORMAL);
		}
	}
}
