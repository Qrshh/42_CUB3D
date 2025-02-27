/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:20:19 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/20 00:42:30 by mosmont          ###   ########.fr       */
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
	if (raycast->texture_coord.y >= \
		(int)all->tab_textures[raycast->wall_face]->height)
		raycast->texture_coord.y = \
		(int)all->tab_textures[raycast->wall_face]->height
			- 1;
}

void	calculate_ray_light(t_raycast *raycast, double player_angle,
		t_flash_light *flash_light)
{
	(void)player_angle;
	flash_light->ray_dir_norm = sqrt(raycast->dda.ray_dir.x
			* raycast->dda.ray_dir.x + raycast->dda.ray_dir.y
			* raycast->dda.ray_dir.y);
	flash_light->player_dir_norm = sqrt(flash_light->player_dir.x
			* flash_light->player_dir.x + flash_light->player_dir.y
			* flash_light->player_dir.y);
	flash_light->scalar_product = (raycast->dda.ray_dir.x
			* flash_light->player_dir.x + raycast->dda.ray_dir.y
			* flash_light->player_dir.y) / (flash_light->ray_dir_norm
			* flash_light->player_dir_norm);
	flash_light->angle_factor = (flash_light->scalar_product + 1.0) / 2.0;
}

void	set_color_shade(t_raycast *raycast, t_flash_light *flash_light,
		bool night_vision)
{
	t_rgb	rgb;

	if (night_vision)
	{
		rgb.r = (uint8_t)(raycast->pixel[0] * flash_light->light_factor * 0.5);
		rgb.g = (uint8_t)(raycast->pixel[1] * flash_light->light_factor * 2);
		rgb.b = (uint8_t)(raycast->pixel[2] * flash_light->light_factor * 0.5);
		if (rgb.r > 200 && rgb.b > 200)
		{
			rgb.r = 255;
			rgb.r = 255;
			rgb.g = 255;
		}
	}
	else
	{
		rgb.r = (uint8_t)(raycast->pixel[0] * flash_light->light_factor);
		rgb.g = (uint8_t)(raycast->pixel[1] * flash_light->light_factor);
		rgb.b = (uint8_t)(raycast->pixel[2] * flash_light->light_factor);
	}
	raycast->color = (rgb.r << 24) \
	| (rgb.g << 16) | (rgb.b << 8) | raycast->pixel[3];
}

void	calculate_color(mlx_texture_t **texture_tab, t_raycast *raycast,
		double player_angle, bool night_vision)
{
	if (raycast->texture_coord.x < 0
		|| raycast->texture_coord.x >= \
		(int)texture_tab[raycast->wall_face]->width)
		raycast->texture_coord.x -= 1;
	if (raycast->texture_coord.y < 0
		|| raycast->texture_coord.y >= \
		(int)texture_tab[raycast->wall_face]->height)
		raycast->texture_coord.y -= 1;
	raycast->tex_index = ((((int)raycast->texture_coord.y
					* (int)texture_tab[raycast->wall_face]->width
					+ (int)raycast->texture_coord.x))
			* texture_tab[raycast->wall_face]->bytes_per_pixel);
	raycast->pixel = \
	&texture_tab[raycast->wall_face]->pixels[raycast->tex_index];
	raycast->color = get_pixel_color(raycast, night_vision, player_angle);
}
