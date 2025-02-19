/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:13:53 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/19 23:56:02 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_border(int i, int j, int height, int len)
{
	return (i == 0 || i == height - 1 || j == 0 || j == len - 1);
}

int	is_invalid_space(char **map, int i, int j, int height)
{
	int	len;

	len = ft_strlen(map[i]);
	return ((j > 0 && ft_isspace(map[i][j - 1])) || (j < len - 1
			&& ft_isspace(map[i][j + 1])) || (i > 0 && ft_isspace(map[i
				- 1][j])) || (i < height - 1 && ft_isspace(map[i + 1][j])));
}

void	adding_line(t_all **all, int fd, int flag)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_line_map(*all, line, fd))
		{
			if (!only_spaces(line))
				flag = 1;
			if (flag && line[0] != '\n')
			{
				(*all)->map = add_line((*all)->map, line);
			}
		}
		else if (only_spaces(line))
			(*all)->infos = add_line((*all)->infos, line);
		free(line);
	}
}
