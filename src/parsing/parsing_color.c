/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:16:04 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/10 21:01:39 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_color(t_all **all, char *color, char id)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)ft_atoi(color);
	while (*color && *color != ',')
		color++;
	color++;
	g = (unsigned char)ft_atoi(color);
	while (*color && *color != ',')
		color++;
	color++;
	b = (unsigned char)ft_atoi(color);
	if (id == 'C')
		(*all)->color_c = (unsigned int)((r << 24) | (g << 16) | (b << 8) | 255);
	else
		(*all)->color_f = (unsigned int)((r << 24) | (g << 16) | (b << 8) | 255);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	setting_color(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			return (0);
		if (ft_atoi(&line[i]) > 255 && line[i] != ' ')
			return (0);
		while (ft_isdigit(line[i]) || line[i] == ' ')
			i++;
		if (line[i] != ',' && flag < 2)
			return (0);
		else
			flag++;
		i++;
	}
	return (1);
}

void	is_valid_color(t_all **all, char *line)
{
	int i;
	int j;
	int k;
	char *id[3];

	id[0] = "F  ";
	id[1] = "C  ";
	i = -1;
	while (++i < 2)
	{
		j = -1;
		k = -1;
		while (line[++k] && line[k] == ' ')
			continue ;
		while (id[i][++j] && line && j < 2)
		{
			if (id[i][j] != line[k++])
				break ;
		}
		if (j == 2)
			break ;
	}
	if (i == 2)
		ft_all_exit(*all, "Color invalid");
	if (!setting_color(&line[k]))
		ft_all_exit(*all, "Color info invalid");
	update_count(all, id[i]);
}