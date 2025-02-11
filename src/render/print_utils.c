/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:12:46 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/11 22:25:50 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_all *all)
{
	double	start_angle;
	double 	end_angle;
	double 	step;
	double	angle;
	int		x;

	start_angle = all->player_angle - (FOV / 2);
	end_angle = all->player_angle + (FOV / 2);
	step = FOV / WIDTH;
	angle = start_angle;

	if (!all->ray_img)
	{
		all->ray_img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(all->mlx, all->ray_img, 0, 0);
	}
	else
		ft_bzero(all->ray_img->pixels, WIDTH * HEIGHT * 4);
	if (!all->wall_img)
	{
		all->wall_img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(all->mlx, all->wall_img, 0, 0);
	}
	else
		ft_bzero(all->wall_img->pixels, WIDTH * HEIGHT * 4);
	
	x = 0;
	while (angle <= end_angle)
	{
		draw_ray(all, angle, x);
		angle += step;
		x++;
	}
}

void	draw_ray(t_all *all, double offset_angle, int x)
{
	t_coord	player_coord;
	t_coord	ray_coord;
	int		map_x;
	int		map_y;
	int		i;
	double	ray_angle;

	player_coord.x = all->player_pos.x;
	player_coord.y = all->player_pos.y;

	// Calculer l'angle du rayon en fonction de la direction du joueur
	ray_angle = (offset_angle);
	ray_coord.x = cos(ray_angle);
	ray_coord.y = sin(ray_angle);

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

	double	distance;
	double	wall_height;
	double	fish_eye;
	double	projected_wall_height;
	int		y_start;
	int		y_end;
	int		y;

	distance = sqrt(pow(player_coord.x - all->player_pos.x, 2)
		+ pow(player_coord.y - all->player_pos.y, 2));
	
	fish_eye = distance * cos(ray_angle - all->player_angle);
	
	projected_wall_height = (WIDTH / 2) / tan(FOV / 2);
	wall_height = (TILE_SIZE * projected_wall_height) / fish_eye;
	
	// if (wall_height > HEIGHT)
	// 	wall_height = HEIGHT;
	y_start = (HEIGHT / 2) - (wall_height / 2);
	y_end = (HEIGHT / 2) + (wall_height / 2);
	// if (y_start < 0)
	// 	y_start = 0;
	// if (y_end >= HEIGHT)
	// 	y_end = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < y_start)
			mlx_put_pixel(all->wall_img, x, y, all->color_c); // Couleur du ciel
		else if (y > y_end)
			mlx_put_pixel(all->wall_img, x, y, all->color_f); // Couleur du sol
		else
			mlx_put_pixel(all->wall_img, x, y, 0x87CEEB); // Couleur du mur
		y++;
	}
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
				square(all, j * TILE_SIZE, i * TILE_SIZE, 0xFF2D00);
			else if (all->map[i][j] == '0')
				square(all, j * TILE_SIZE, i * TILE_SIZE, 0xFFFFFF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(all->mlx, all->img, all->player_pos.x, all->player_pos.y);
}
