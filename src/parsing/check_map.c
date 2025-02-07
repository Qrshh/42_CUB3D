/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:29:01 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/07 16:45:58 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int ft_isspace(char c)
{
    if(c == ' ')
        return(1);
    return(0);
}

int	is_map_close(char **map)
{
	int	i;
	int	j;
	int	num_lines;
	int	len;

	i = 0;
	num_lines = 0;
	while (map[num_lines])
		num_lines++;
	j = 0;
	while (map[0][j])
	{
		if (!ft_isspace(map[0][j]) && map[0][j] != '1')
			return (0);
		j++;
	}
	j = 0;
	while (map[num_lines - 1][j])
	{
		if (!ft_isspace(map[num_lines - 1][j]) && map[num_lines - 1][j] != '1')
			return (0);
		j++;
	}
	while (i < num_lines)
	{
		j = 0;
		len = strlen(map[i]);
		while (len > 0 && ft_isspace(map[i][len - 1]))
			len--;
		while (j < len && ft_isspace(map[i][j]))
			j++;
		if (len > 0 && map[i][j] != '1')
			return (0);
		if (len > 0 && map[i][len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	forbidden_char(char **map)
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
	// retourne 1 si starting pos est different de 1, sinon ca retourne 0
}

void	check_valid_map(t_all **all)
{
	if (!(*all)->map)
		ft_all_exit(*all, "Map is invalid");
	if (!forbidden_char((*all)->map))
		ft_all_exit(*all, "Wrong char inside map");
	if (!is_map_close((*all)->map))
		ft_all_exit(*all, "Map is not close");
	// check si la starting pos pue la merde ou pas
}