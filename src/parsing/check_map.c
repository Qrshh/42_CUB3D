/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:29:01 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/17 18:02:17 by abesneux         ###   ########.fr       */
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
	int	height; /** CHANGE TO HEIGHT FOR BETTER UNDERSTANDING **/

	i = -1;
	while (map[++i])
		;
	height = i;
	i = -1;
	while (++i < height) // CHANGE CONDITION TO i < height
	{
		j = -1;
		len = ft_strlen(map[i]);
		while (++j < len)
		{
			if (ft_isspace(map[i][j]))
				continue ;
			if (i == 0 || i == height - 1 || j == 0 || j == len - 1)
			{
				if (map[i][j] != '1')
					return (0);
			}
			else if (is_allowed_char(map[i][j]))
			{
				if ((j > 0 && (ft_isspace(map[i][j - 1]) || map[i][j - 1] == '\0'))
					|| (j < len - 1 && (ft_isspace(map[i][j + 1]) || map[i][j + 1] == '\0'))
					|| (i > 0 && (ft_isspace(map[i - 1][j]) || map[i - 1][j] == '\0'))
					|| (i < height - 1 && (ft_isspace(map[i + 1][j]) || map[i + 1][j] == '\0')))
				{
					return (0); 
				}
				// CHANGE IF FOR CHECK \0
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
				&& map[i][j] != 'S' && map[i][j] != 'D' && map[i][j] != 'W')
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
