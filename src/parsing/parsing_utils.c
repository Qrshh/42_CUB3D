/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:25 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/19 22:58:13 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_allowed_char(char c)
{
	if (c == ' ' || c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W'
		|| c == 'D')
		return (1);
	return (0);
}

char	**add_line(char **tab, char *line)
{
	char	**newtab;
	int		size;
	int		i;

	size = 0;
	while (tab && tab[size])
		size++;
	newtab = ft_calloc(size + 2, sizeof(char *));
	i = -1;
	while (++i < size && tab)
		newtab[i] = ft_strdup(tab[i]);
	newtab[i] = ft_strdup(line);
	newtab[++i] = NULL;
	free_tab(tab);
	return (newtab);
}

int	is_line_map(t_all *all, char *line, int fd)
{
    int	i;

    i = 0;
    while (line[i] && line[i] == ' ')
        i++;
    if (!line[i] || line[i] == 'N' || line[i] == 'E' || line[i] == 'S'
        || line[i] == 'W' || line[i] == 'F' || line[i] == 'C' || line[i] == 'D')
        return (0);
	i--;
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != '\n'
            && line[i] != 'N' && line[i] != 'D' && line[i] != 'E'
            && line[i] != 'S' && line[i] != 'W' && line[i] != ' '
            && line[i] != '\t')
        {
			free(line);
			close(fd);
            ft_all_exit(all, "Forbidden char in map");
        }
        if (line[i + 1] && line[i + 1] == '\n')
            line[i + 1] = '\0';
        i++;
    }
    return (1);
}

void	init_ptr(t_all **all)
{
	int	i;

	*all = ft_calloc(1, sizeof(t_all));
	(*all)->map = NULL;
	(*all)->infos = NULL;
	(*all)->player_pos.x = 0;
	(*all)->player_pos.y = 0;
	(*all)->player_angle = 0;
	(*all)->starting_dir = 0;
	(*all)->f = 0;
	(*all)->c = 0;
	(*all)->no = 0;
	(*all)->so = 0;
	(*all)->we = 0;
	(*all)->ea = 0;
	(*all)->d = 0;
	(*all)->color_c = 0;
	(*all)->color_f = 0;
	(*all)->wall_img = NULL;
	(*all)->fov = FOV * (M_PI / 180);
	i = -1;
	while (++i < NB_TEXT)
		(*all)->tab_textures[i] = NULL;
}

int	check_format(char *str, char *cmp)
{
	int	i;

	i = 0;
	while (str[i] && ft_strcmp(&str[i], cmp) != 0)
		i++;
	if (ft_strcmp(&str[i], cmp) == 0)
		return (0);
	return (1);
}
