/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:35 by abesneux          #+#    #+#             */
/*   Updated: 2025/01/31 20:09:35 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (str[i - 3] != '.' || str[i - 2] != 'c' || str[i - 1] != 'u'
		|| str[i] != 'b')
		return (1);
	return (0);
}

int	check_opening(char *file, int *fd)
{
	*fd = open(file, O_DIRECTORY);
	if (*fd != -1 && *fd > 2)
		return (close(*fd), 1);
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (1);
	return (0);
}

int	take_info_map(t_info *info, int fd_map)
{
	char	*line;
	int		i;

	i = 0;
	info->map = malloc(sizeof(char *) * 128); // 128 estimation taille maximale
	if (!info->map)
		return (1);
	line = get_next_line(fd_map);
	while (line != NULL)
	{
		info->map[i] = ft_strdup(line);
		if (!info->map[i])
		{
			free(line);
			return (1);
		}
		ft_printf("Line %d: %s", i, info->map[i]);
		free(line);
		line = get_next_line(fd_map);
		i++;
	}
	info->map[i] = NULL;
	ft_printf("\n");
	return (0);
}
