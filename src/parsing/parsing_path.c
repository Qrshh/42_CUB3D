/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:29:25 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/19 22:46:29 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

int	is_path_valid(char *path, t_all **all, int index)
{
	char	*str;
	// int		fd;

	str = ft_strtrim(path, "\n ");
	if (ft_strstr(str, ".png") == NULL)
	{
		free(str);
		return (0);
	}
	// fd = open(str, O_RDONLY);
	// if (fd == -1)
	// {
	// 	free(str);
	// 	return (0);
	// }
	// close(fd);
	(*all)->tab_textures[index] = mlx_load_png(str);
	free(str);
	if (!(*all)->tab_textures[index])
		return (0);
	return (1);
}

void	update_count(t_all **all, char *id)
{
	if (ft_strcmp(id, "NO ") == 0)
		(*all)->no += 1;
	else if (ft_strcmp(id, "SO ") == 0)
		(*all)->so += 1;
	else if (ft_strcmp(id, "WE ") == 0)
		(*all)->we += 1;
	else if (ft_strcmp(id, "EA ") == 0)
		(*all)->ea += 1;
	else if (ft_strcmp(id, "F ") == 0)
		(*all)->f += 1;
	else if (ft_strcmp(id, "C ") == 0)
		(*all)->c += 1;
	else if (ft_strcmp(id, "DO ") == 0)
		(*all)->d += 1;
	if ((*all)->c > 1 || (*all)->f > 1 || (*all)->no > 1 || (*all)->so > 1
		|| (*all)->we > 1 || (*all)->ea > 1 || (*all)->d > 1)
		ft_all_exit(*all, "Infos are existing more than one time");
}

int	id_line(char *line, t_all **all, int i)
{
	char	*tab[5];
	int		j;
	int		k;

	tab[0] = "NO ";
	tab[1] = "SO ";
	tab[2] = "EA ";
	tab[3] = "WE ";
	tab[4] = "DO ";
	while (++i < 5)
	{
		k = -1;
		while (line[++k] && line[k] == ' ')
			;
		j = -1;
		while (tab[i][++j] && line && j < 3)
			if (tab[i][j] != line[k++])
				break ;
		if (j == 3)
			break ;
	}
	if (i == 5)
		return (1);
	update_count(all, tab[i]);
	return (0);
}

int	get_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] == ' ')
		continue ;
	if (line[i] == 'N')
		return (0);
	else if (line[i] == 'S')
		return (1);
	else if (line[i] == 'W')
		return (2);
	else if (line[i] == 'E')
		return (3);
	else
		return (4);
}

void	is_info_valid(t_all **all, char *line)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] == ' ')
		continue ;
	if (!id_line(line, all, -1))
	{
		if (!is_path_valid(&line[i + 2], all, get_line(line)))
			ft_all_exit(*all, "Informations path is invalid");
	}
	else
	{
		is_valid_color(all, line);
		update_color(all, &line[i + 1], line[0]);
	}
}
