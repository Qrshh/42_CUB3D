/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:12:18 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/07 19:23:30 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	only_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '\n')
		if (!(str[i] >= '\t' && str[i] <= '\r') && str[i] != ' ')
			return (1);
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_all_exit(t_all *all, char *str)
{
	free_all(all);
	if (str)
		exit_error(str);
}

void	free_all(t_all *all)
{
	int	i;

	if (all->map)
		free_tab(all->map);
	if (all->infos)
		free_tab(all->infos);
	i = -1;
	while (++i < 4)
	{
		if (all->tab_textures[i])
			mlx_delete_texture(all->tab_textures[i]);
	}
	mlx_terminate(all->mlx);
	free(all);
}

void	exit_error(char *str)
{
	ft_printf("Error\n%s\n", str);
	exit(EXIT_FAILURE);
}
