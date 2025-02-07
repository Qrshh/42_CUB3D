/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:29:01 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/07 18:42:37 by abesneux         ###   ########.fr       */
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
	int	len;
	int	width;

	i = -1;
	while (map[++i])
		;
	width = i;
	i = -1;
	while (map[++i])
	{
		j = -1;
		len = ft_strlen(map[i]);
		while (++j < len)
		{
			if (ft_isspace(map[i][j]))
				continue ;
			if (i == 0 || i == width - 1 || j == 0 || j == len - 1)
			{
				if (map[i][j] != '1')
					return (0);
			}
			else if (is_allowed_char(map[i][j]))
			{
				if ((j > 0 && ft_isspace(map[i][j - 1])) || (j < len - 1
						&& ft_isspace(map[i][j + 1])) || (i > 0
						&& ft_isspace(map[i - 1][j])) || (i < width - 1
						&& ft_isspace(map[i + 1][j])))
				{
					return (0);
				}
			}
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
			if (map[i][j] && map[i][j] != ' ' && map[i][j] != '1'
				&& map[i][j] != 'N' && map[i][j] != '0' && map[i][j] != 'E'
				&& map[i][j] != 'S' && map[i][j] != 'W')
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
			if (ft_strchr("NEWS", map[i][j]))
				starting_pos++;
		}
	}
	return (starting_pos != 1);
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
