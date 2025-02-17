/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:31 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/17 15:21:19 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	escape(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
}

int	main(int ac, char **av)
{
	t_all	*all;

	parsing(&all, ac, av);
	// all->sprite_texture[0] = mlx_load_png("textures/barrel.png");
	// all->sprites[0] = (t_sprite){3.5, 5.5, 0, 0};
	// all->sprites[1] = (t_sprite){5.5, 5.5, 0, 0};
	// all->num_sprites = 1;
	mlx_loop_hook(all->mlx, escape, all);
	mlx_loop_hook(all->mlx, moove_fw_bw, all);
	mlx_loop_hook(all->mlx, moove_left_right, all);
	mlx_loop_hook(all->mlx, fov_mooves, all);
	mlx_key_hook(all->mlx, toggle, all);
	mlx_loop(all->mlx);
	ft_all_exit(all, NULL);
}
