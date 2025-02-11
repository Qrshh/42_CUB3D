/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:12:46 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/11 19:14:59 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_ray(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			mlx_put_pixel(all->ray_img, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

void	draw_ray(t_all *all, double angle)
{
	t_coord	player_coord;
	t_coord	ray_coord;
	int		map_x;
	int		map_y;
	int		i;

	player_coord.x = all->player_pos.x;
	player_coord.y = all->player_pos.y;
	ray_coord.x = cos(angle);
	ray_coord.y = sin(angle);
	i = -1;
	while (++i < 500)
	{
		player_coord.x += ray_coord.x;
		player_coord.y += ray_coord.y;
		map_x = (int)(player_coord.x / TILE_SIZE);
		map_y = (int)(player_coord.y / TILE_SIZE);
		if (all->map[map_y][map_x] == '1')
			break ;
		mlx_put_pixel(all->ray_img, (int)player_coord.x, (int)player_coord.y, all->color_c);
	}
	mlx_put_pixel(all->ray_img, 250, 250, all->color_c);
	mlx_image_to_window(all->mlx, all->ray_img, 0, 0);
}

void	square(t_all *all, int x, int y, int color)
{
	int	i;
	int	j;
	mlx_image_t	*square;

	i = 0;
	square = mlx_new_image(all->mlx, TILE_SIZE, TILE_SIZE);
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (i == 0 || i == TILE_SIZE - 1 || j == 0 || j == TILE_SIZE - 1)
				mlx_put_pixel(square, i, j, 0x000000);
			else
				mlx_put_pixel(square, i, j, color);
			j++;
		}
		i++;
	}
	if (mlx_image_to_window(all->mlx, square, x, y) < 0)
		ft_all_exit(all, "mlx_image_to_window failed in square");
}

int	only_direction(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void	draw_map(t_all *all)
{
	int	i = 0;
	int	j = 0;

	while (all->map && all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				square(all, j * TILE_SIZE, i * TILE_SIZE, 0xECCBD9);
			else if (all->map[i][j] == '0')
				square(all, j * TILE_SIZE, i * TILE_SIZE, 0x97D2FB);
			j++;
		}
		i++;
	}
	mlx_image_to_window(all->mlx, all->img, all->player_pos.x, all->player_pos.y);

}
