/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:31 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/07 19:24:19 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	escape(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
}

int	main(int ac, char **av)
{
	t_all	*all;
	int		i;

	parsing(&all, ac, av);
	if (!all->map)
		ft_all_exit(all, "infos is NULL in main");
	i = -1;
	while (all->map && all->map[++i])
		ft_printf("%s\n", all->map[i]);
	mlx_loop_hook(all->mlx, escape, all);
	mlx_loop(all->mlx);
	ft_all_exit(all, NULL);
}
