/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:31 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/19 17:40:47 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void welcome(void)
{
	ft_printf("\n\
		\033[1;36m----------------------------------\n\
			  Bienvenue dans Cub3D !\n\
		----------------------------------\033[0m\n\
		\033[1;33mCommandes :\033[0m\n\
		\033[1;32m- Se déplacer :\033[0m WASD\n\
		\033[1;32m- Diriger la caméra :\033[0m L and R arrows\n\
		\033[1;32m- Allumer la flashlight :\033[0m F\n\
		\033[1;32m- Diriger la caméra :\033[0m Souris (P pour activer/désactiver)\n\
		\033[1;32m- Afficher la minimap :\033[0m (M pour acitver/desactiver)\n\
		");		
}

void	escape(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
}

int	main(int ac, char **av)
{
	t_all			*all;
	mlx_texture_t	*txt;

	welcome();
	parsing(&all, ac, av);
	init_nightvision_text(all);
	txt = mlx_load_png("textures/arrow_minimap.png");
	// PAS TOUCHE PLZ
	all->player_img = mlx_texture_to_image(all->mlx, txt);
	all->num_sprites = 1;
	all->sprites[0] = (t_sprite){1.5 * TILE_SIZE, 1.5 * TILE_SIZE, 0, 0};
	all->sprite_texture[0] = mlx_load_png("textures/barrel.png");
	mlx_loop_hook(all->mlx, escape, all);
	mlx_loop_hook(all->mlx, moove_fw_bw, all);
	mlx_loop_hook(all->mlx, moove_left_right, all);
	mlx_loop_hook(all->mlx, fov_mooves, all);
	mlx_key_hook(all->mlx, toggle, all);
	mlx_loop(all->mlx);
	ft_all_exit(all, NULL);
}
