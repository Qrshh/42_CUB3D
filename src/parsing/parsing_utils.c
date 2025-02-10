/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:25 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/10 21:25:24 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_allowed_char(char c)
{
	if (c == ' ' || c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
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

int	is_line_map(t_all *all, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == 'N' || line[i] == 'E' || line[i] == 'S'
		|| line[i] == 'W' || line[i] == 'F' || line[i] == 'C')
		return (0);
	line--;
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '\n'
			&& line[i] != 'N' && line[i] != 'E' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != ' ' && line[i] != '\t')
		{
			ft_all_exit(all, "Forbidden char in map");
		}
		if (line[i + 1] && line[i + 1] == '\n')
			line[i + 1] = '\0';
	}
	return (1);
}

void	init_ptr(t_all **all)
{
	int	i;
	*all = ft_calloc(1, sizeof(t_all));
	(*all)->map = NULL;
	(*all)->infos = NULL;
	(*all)->mlx = mlx_init(WIDTH, HEIGHT, "YOUPI", 1);
	i = -1;
	while (++i < 4)
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
