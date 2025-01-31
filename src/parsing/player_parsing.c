/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:36:57 by abesneux          #+#    #+#             */
/*   Updated: 2025/01/31 19:26:16 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_direction2(t_info *info)
{
	info->dir_x = -1;
	info->dir_y = 0;
	info->plane_x = 0;
	info->plane_y = -0.66;
}

void	set_player_direction(t_info *info, char orientation)
{
	if (orientation == 'N')
	{
		info->dir_x = 0;
		info->dir_y = -1;
		info->plane_x = 0.66;
		info->plane_y = 0;
	}
	else if (orientation == 'S')
	{
		info->dir_x = 0;
		info->dir_y = 1;
		info->plane_x = -0.66;
		info->plane_y = 0;
	}
	else if (orientation == 'E')
	{
		info->dir_x = 1;
		info->dir_y = 0;
		info->plane_x = 0;
		info->plane_y = 0.66;
	}
	else if (orientation == 'W')
		set_player_direction2(info);
}

int	calculating_position_player(t_info *info, int x, int y, char *player_char)
{
	if ((info->map[y][x] == 'N' || info->map[y][x] == 'S'
		|| info->map[y][x] == 'E' || info->map[y][x] == 'W') && (info->map[y][x] != ' '))
	{
		if (*player_char != '\0')
        {
            ft_printf("Multiple players found: already found player at (%f, %f)\n", info->pos_x, info->pos_y);
			return (exit_error("There are multiples players found"), 1);
        }
		info->pos_x = x + 0.5; // on rajoute pour eviter les colisions
		info->pos_y = y + 0.5;
		*player_char = info->map[y][x];
		set_player_direction(info, *player_char);
		info->map[y][x] = '0'; // on met un sol a la place du player pour pas qu'il y ai du vide
	}
	return (0);
}

int	find_player_position(t_info *info)
{
	int		x;
	int		y;
	char	player_char;

	player_char = '\0';
	y = 0;
	while (info->map[y])
	{
		x = 0;
		while (info->map[y][x])
		{
			if (calculating_position_player(info, x, y, &player_char))
            {
                free_double(info->map);
				return (1);
            }
			x++;
		}
		y++;
	}
	if (player_char == '\0')
		return (exit_error("No player position found"), 1);
	return (0);
}
