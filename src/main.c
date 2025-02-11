/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:31 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/11 22:43:50 by mosmont          ###   ########.fr       */
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
	// mlx_texture_t *arrow = mlx_load_png("textures/arrow_minimap.png");
	// all->img = mlx_texture_to_image(all->mlx, arrow);
	// all->ray_img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	mlx_loop_hook(all->mlx, event_listener, all);
	mlx_loop_hook(all->mlx, fov_mooves, all);
	mlx_loop(all->mlx);
	ft_all_exit(all, NULL);
}
