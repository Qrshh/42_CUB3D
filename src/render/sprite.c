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
