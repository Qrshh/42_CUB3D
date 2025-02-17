/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:29:01 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/17 23:31:31 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_map_close(char **map)
{
	int	i;
	int	j;
	int	height;
	int	len;

	i = 0;
	while (map[i])
		i++;
	height = i;
	i = -1;
	while (++i < height)
	{
		len = ft_strlen(map[i]);
		j = -1;
		while (++j < len)
		{
			if (!ft_isspace(map[i][j]) && ((is_border(i, j, height, len)
						&& map[i][j] != '1') || (is_allowed_char(map[i][j])
						&& is_invalid_space(map, i, j, height))))
				return (0);
		}
	}
	return (1);
}

int	forbidden_char(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_allowed_char(map[i][j]) && map[i][j] != '1')
				return (0);
		}
	}
	return (1);
}

int	check_starting_pos(char **map)
{
	int	i;
	int	j;
	int	starting_pos;

	i = -1;
	starting_pos = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S'
				|| map[i][j] == 'W')
				starting_pos++;
		}
	}
	if (starting_pos == 1)
		return (1);
	return (0);
}

void	check_valid_map(t_all **all)
{
	if (!(*all)->map)
		ft_all_exit(*all, "Map is invalid");
	if (!forbidden_char((*all)->map))
		ft_all_exit(*all, "Wrong char inside map");
	if (!is_map_close((*all)->map))
		ft_all_exit(*all, "Map is not close");
	if (!check_starting_pos((*all)->map))
		ft_all_exit(*all, "Wrong starting position");
}
