/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 01:13:03 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/19 21:15:59 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_ray_light(t_raycast *raycast, double player_angle,
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

static int	set_color_shade(t_flash_light *flash_light, bool night_vision,
	uint8_t *pixel)
{
	t_rgb	rgb;

	if (night_vision)
	{
		rgb.r = (uint8_t)(pixel[0] * flash_light->light_factor * 0.8);
		rgb.g = (uint8_t)(pixel[1] * flash_light->light_factor * 1.7);
		rgb.b = (uint8_t)(pixel[2] * flash_light->light_factor * 0.8);
		if (rgb.r > 200 && rgb.b > 200)
		{
			rgb.r = 255;
			rgb.r = 255;
			rgb.g = 255;
		}
	}
	else
	{
		rgb.r = (uint8_t)(pixel[0] * flash_light->light_factor);
		rgb.g = (uint8_t)(pixel[1] * flash_light->light_factor);
		rgb.b = (uint8_t)(pixel[2] * flash_light->light_factor);
	}
	return ((rgb.r << 24) | (rgb.g << 16) | (rgb.b << 8) | pixel[3]);
}

int	get_pixel_color(t_raycast *raycast, bool night_vision,
		double player_angle)
{
	t_flash_light	flash_light;

	if (night_vision)
		flash_light.dst_factor = 1.0 / (1.0 + 0.005 * raycast->fish_eye);
	else
		flash_light.dst_factor = 1.0 / (1.0 + DIST_LIGHT * raycast->fish_eye);
	if (flash_light.dst_factor > 1.0)
		flash_light.dst_factor = 1.0;
	flash_light.player_dir.x = cos(player_angle);
	flash_light.player_dir.y = sin(player_angle);
	calculate_ray_light(raycast, player_angle, &flash_light);
	if (night_vision)
	{
		flash_light.falloff = 1.0 / (1.0 + DIST_LIGHT
				* pow(fmax(raycast->perp_wall_dist, 25), 1.5));
	}
	else
	{
		flash_light.falloff = 1.0 / (1.0 + 0.090
				* pow(raycast->perp_wall_dist, 1.5));
	}
	flash_light.angle_factor *= flash_light.falloff;
	flash_light.light_factor = flash_light.dst_factor
		* flash_light.angle_factor;
	return (set_color_shade(&flash_light, night_vision, raycast->pixel));
}
