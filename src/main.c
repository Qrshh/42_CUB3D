/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:31 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/16 01:44:59 by mosmont          ###   ########.fr       */
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
	ft_printf("Player Position: (%f, %f)\n", all->player_pos.x, all->player_pos.y);
	ft_printf("Pointer: %p\n", all);
	ft_printf("Map: %c\n", all->map[1][1]);
	// all->img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	printf("Pointer dans main: %u\n", all->tab_textures[1]->pixels[1520]);
	all->ray_img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	// if (!all->ray_img)
	// {
	// 	all->ray_img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	// 	mlx_image_to_window(all->mlx, all->ray_img, 0, 0);
	// }
	// else
	// 	ft_bzero(all->ray_img->pixels, WIDTH * HEIGHT * 4);
	// if (!all->wall_img)
	// {
	// 	all->wall_img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	// 	mlx_image_to_window(all->mlx, all->wall_img, 0, 0);
	// }
	// else
	// 	ft_bzero(all->wall_img->pixels, WIDTH * HEIGHT * 4);
	// draw_ray(all, (M_PI / 2) - (FOV / 2), WIDTH / 2);
	// draw_map(all);
	mlx_loop_hook(all->mlx, escape, all);
	mlx_loop_hook(all->mlx, moove_fw_bw, all);
	mlx_loop_hook(all->mlx, moove_left_right, all);
	mlx_loop_hook(all->mlx, fov_mooves, all);
	mlx_key_hook(all->mlx, toggle, all);
	mlx_loop(all->mlx);
	ft_all_exit(all, NULL);
}
