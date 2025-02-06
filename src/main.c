/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:31 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/06 21:48:13 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_all *all;
	parsing(&all, ac, av);
	if (!all->map)
		ft_all_exit(all, "infos is NULL in main");
	int i = -1;
	while (all->map && all->map[++i])  // Vérification que all->infos est valide
		ft_printf("%d %s\n", i, all->map[i]);

}
