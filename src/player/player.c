/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:10:58 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/11 00:32:58 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move(void *param)
{
	t_all *all = (t_all *)param;

	int i = all->player_pos.y / TILE_SIZE; // Ligne actuelle
	int j = all->player_pos.x / TILE_SIZE; // Colonne actuelle

	// W = Aller vers le haut, donc vérifier la ligne au-dessus (i - 1)
	if (mlx_is_key_down(all->mlx, MLX_KEY_W))
	{
		ft_printf("Player Grid Position: (%d, %d)\n", i, j);
		all->player_pos.y -= 1; // Déplacement vers le haut
		all->img->instances[0].y -= 1;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
	// if (mlx_is_key_down(all->mlx, MLX_KEY_W))
	// 	all->img->instances[0].y -= 5;
	if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		all->img->instances[0].y += 5;
	if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		all->img->instances[0].x -= 5;
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		all->img->instances[0].x += 5;
}