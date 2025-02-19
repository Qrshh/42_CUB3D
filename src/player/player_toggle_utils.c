/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_toggle_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:13:14 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/19 21:48:20 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_nightvision_text(t_all *all)
{
	if (!all || !all->mlx)
		return ;
	all->text_img = NULL;
}

void	toggle_nightvision(t_all *all)
{
	if (!all || !all->mlx)
		return ;
	all->night_vision = !all->night_vision;
	if (all->text_img)
	{
		mlx_delete_image(all->mlx, all->text_img);
		all->text_img = NULL;
	}
	if (all->night_vision)
		all->text_img = mlx_put_string(all->mlx, "NIGHT VISION ON", WIDTH - 200,
				20);
}
