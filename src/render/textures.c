/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:20:19 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/19 01:13:40 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_wall_face(t_raycast *raycast, t_all *all, t_dda *dda)
{
	if (dda->side == 0)
	{
		if (dda->ray_dir.x < 0)
			raycast->wall_face = WEST;
		else
			raycast->wall_face = EAST;
	}
	else
	{
		if (dda->ray_dir.y < 0)
			raycast->wall_face = NORTH;
		else
			raycast->wall_face = SOUTH;
	}
	if (all->map[dda->map.y][dda->map.x] == 'D')
		raycast->wall_face = 4;
}

void	calcul_tex(t_all *all, t_raycast *raycast, int y)
{
	double	wall_x;

	if (raycast->dda.side == 0)
		wall_x = (all->player_pos.y + raycast->perp_wall_dist
				* raycast->dda.ray_dir.y) / TILE_SIZE;
	else
		wall_x = (all->player_pos.x + raycast->perp_wall_dist
				* raycast->dda.ray_dir.x) / TILE_SIZE;
	wall_x -= floor(wall_x);
	raycast->texture_coord.x = (int)(wall_x
			* (double)all->tab_textures[raycast->wall_face]->width + 0.5);
	raycast->texture_coord.y = ((y - raycast->y_start)
			* all->tab_textures[raycast->wall_face]->height
			/ raycast->wall_height);
	if (raycast->texture_coord.y
		>= (int)all->tab_textures[raycast->wall_face]->height)
		raycast->texture_coord.y
			= (int)all->tab_textures[raycast->wall_face]->height - 1;
}

void	calculate_color(mlx_texture_t **texture_tab, t_raycast *raycast,
		double player_angle, bool night_vision)
{

	raycast->tex_index = ((((int)raycast->texture_coord.y
					* (int)texture_tab[raycast->wall_face]->width
					+ (int)raycast->texture_coord.x)
				) * texture_tab[raycast->wall_face]->bytes_per_pixel);
	raycast->pixel
		= &texture_tab[raycast->wall_face]->pixels[raycast->tex_index];
	raycast->color = get_pixel_color(raycast, raycast->pixel,
			night_vision, player_angle);
}
