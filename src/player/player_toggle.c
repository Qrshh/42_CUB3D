/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_toggle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:04:12 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/12 21:00:44 by abesneux         ###   ########.fr       */
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

void	toggle(mlx_key_data_t keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_RELEASE)
		toggle_minimap(all);
	else if (keydata.key == MLX_KEY_P && keydata.action == MLX_RELEASE)
		toggle_mouse_fov(all);
}
