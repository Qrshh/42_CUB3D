/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:22:35 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/17 19:56:45 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_step(t_all *all, t_dda *dda)
{
	if (dda->ray_dir.x < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (all->player_pos.x - (dda->map.x * TILE_SIZE))
			/ fabs(dda->ray_dir.x);
	}
	else
	{
		dda->step.x = 1;
		dda->side_dist.x = ((dda->map.x + 1) * TILE_SIZE - all->player_pos.x)
			/ fabs(dda->ray_dir.x);
	}

	if (dda->ray_dir.y < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (all->player_pos.y - (dda->map.y * TILE_SIZE))
			/ fabs(dda->ray_dir.y);
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = ((dda->map.y + 1) * TILE_SIZE - all->player_pos.y)
			/ fabs(dda->ray_dir.y);
	}
}

void	dda_loop(t_dda *dda, char **map)
{
	while (dda->hit == 0)
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->delta_dist.x;
			dda->map.x += dda->step.x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist.y += dda->delta_dist.y;
			dda->map.y += dda->step.y;
			dda->side = 1;
		}
		if (map[dda->map.y][dda->map.x] == '1'
			|| map[dda->map.y][dda->map.x] == 'D')
			dda->hit = 1;
	}
}