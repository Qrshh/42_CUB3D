/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:43:56 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/11 23:54:26 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_all **all, int i, int j)
{
	(*all)->player_pos.x = (j + 0.5) * TILE_SIZE;
	(*all)->player_pos.y = (i + 0.5) * TILE_SIZE;
	(*all)->starting_dir = (*all)->map[i][j];
	if ((*all)->map[i][j] == 'N')
		(*all)->player_angle = 3 * M_PI / 2;
	else if ((*all)->map[i][j] == 'E')
		(*all)->player_angle = 0;
	else if ((*all)->map[i][j] == 'S')
		(*all)->player_angle = M_PI / 2;
	else if ((*all)->map[i][j] == 'W')
		(*all)->player_angle = M_PI;
	(*all)->map[i][j] = '0';
}
