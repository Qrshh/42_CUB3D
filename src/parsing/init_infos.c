/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:34 by abesneux          #+#    #+#             */
/*   Updated: 2025/01/31 19:19:09 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_infos(t_info *info)
{
	int	i;

	i = 0;
	info->pos_x = -1;
	info->pos_y = -1;
	info->dir_x = -1;
	info->dir_y = -1;
	info->plane_x = -1;
	info->plane_y = -1;
	info->map = NULL;
	while (i < 4)
	{
		info->texture_path[i] = NULL;
		info->textures[i] = NULL;
        i++;
	}
	info->floor_color = -1;
	info->ceiling_color = -1;
	info->mlx = NULL;
	info->win = NULL;
	info->img = NULL;
	info->addr = NULL;
	return (0);
}
