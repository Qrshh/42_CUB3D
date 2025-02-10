/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:10:58 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/10 22:45:35 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move(mlx_key_data_t keydata, void *param)
{
    t_all *all = (t_all *)param;
    static int old_x = 0;
    static int old_y = 0;

    if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(all->mlx);

    // Sauvegarde la position actuelle
    old_x = all->player_pos.x;
    old_y = all->player_pos.y;

    // Mise à jour de la position
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT)
        all->player_pos.y -= 5;
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT)
        all->player_pos.y += 5;
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT)
        all->player_pos.x -= 5;
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT)
        all->player_pos.x += 5;

    // Efface uniquement l'ancienne position
	square(all, old_x, old_y, 0x000000FF); // Fond noir// Fond noir

    // Dessine le joueur à la nouvelle position
    square(all, all->player_pos.x, all->player_pos.y, all->color_f);
}