/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:55:02 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/19 19:45:18 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_sprite_infos(t_all *all)
{
	int		i;
	double	dx;
	double	dy;
	double	sprite_angle;

	i = 0;
	while (i < all->num_sprites)
	{
		dx = all->sprites[i].x - all->player_pos.x;
		dy = all->sprites[i].y - all->player_pos.y;
		all->sprites[i].distance = sqrt(dx * dx + dy * dy);
		sprite_angle = atan2(dy, dx);
		while (sprite_angle - all->player_angle > M_PI)
			sprite_angle -= 2 * M_PI;
		while (sprite_angle - all->player_angle < -M_PI)
			sprite_angle += 2 * M_PI;
		if (fabs(sprite_angle - all->player_angle) > (all->fov / 2))
			all->sprites[i].distance = -1;
		// printf("sprite dist %f sprite angle %f\n",
		// 	all->sprites[i].distance, sprite_angle);
		i++;
	}
}
// printf("sprite dist %f sprite angle %f\n",
// 			all->sprites[i].distance, sprite_angle);

void	sort_sprites(t_all *all)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = -1;
	while (++i < all->num_sprites)
	{
		j = i + 1;
		while (j < all->num_sprites)
		{
			if (all->sprites[i].distance < all->sprites[j].distance)
			{
				temp = all->sprites[i];
				all->sprites[i] = all->sprites[j];
				all->sprites[j] = temp;
			}
			j++;
		}
	}
}
