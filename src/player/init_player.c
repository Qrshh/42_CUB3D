/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:43:56 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/11 23:23:34 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_all **all, int i, int j)
{
    (*all)->player_pos.x = (j + 0.5) * TILE_SIZE;  // Position centrée sur la case
    (*all)->player_pos.y = (i + 0.5) * TILE_SIZE;
    (*all)->starting_dir = (*all)->map[i][j];  // Direction de départ du joueur

    // Définir l'angle du joueur en fonction de la direction
    if ((*all)->map[i][j] == 'N')
        (*all)->player_angle = 3 * M_PI / 2;  // Nord (regarde vers le haut)
    else if ((*all)->map[i][j] == 'E')
        (*all)->player_angle = 0;  // Est (regarde vers la droite)
    else if ((*all)->map[i][j] == 'S')
        (*all)->player_angle = M_PI / 2;  // Sud (regarde vers le bas)
    else if ((*all)->map[i][j] == 'W')
        (*all)->player_angle = M_PI;  // Ouest (regarde vers la gauche)

    // Remplacer la case du joueur par du sol
    (*all)->map[i][j] = '0'; 
}

