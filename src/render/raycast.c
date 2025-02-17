/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:12:46 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/17 20:18:50 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_all *all)
{
	double	start_angle;
	double	end_angle;
	double	step;
	double	angle;
	int		x;

	start_angle = all->player_angle - (all->fov / 2);
	end_angle = all->player_angle + (all->fov / 2);
	step = all->fov / WIDTH;
	angle = start_angle;
	refresh_image(all->mlx, &all->wall_img);
	x = 0;
	while (angle < end_angle)
	{
		draw_ray(all, angle, x);
		angle += step;
		x++;
	}
	draw_minimap(all);
}

void	calculate_ray(t_raycast *raycast)
{
	double	project;

	raycast->wall_height = (int)(TILE_SIZE * HEIGHT
			/ raycast->fish_eye_correction);
	raycast->y_start = -raycast->wall_height / 2 + HEIGHT / 2;
	raycast->y_end = raycast->wall_height / 2 + HEIGHT / 2;
}

void	draw_wall(t_all *all, t_raycast *raycast, int x)
{
	int			y;

	calculate_ray(raycast);
	y = 0;
	while (y < HEIGHT)
	{
		if (y < raycast->y_start)
			mlx_put_pixel(all->wall_img, x, y, all->color_c);
		else if (y > raycast->y_end)
			mlx_put_pixel(all->wall_img, x, y, all->color_f);
		else
		{
			calcul_tex(all, raycast, y);
			calculate_color(all->tab_textures, raycast, all->player_angle);
			mlx_put_pixel(all->wall_img, x, y, raycast->color);
		}
		y++;
	}
}

void	draw_ray(t_all *all, double angle, int x)
{
	t_dda		dda;
	t_raycast	raycast;

	dda.ray_dir.x = cos(angle);
	dda.ray_dir.y = sin(angle);
	dda.map.x = (int)(all->player_pos.x / TILE_SIZE);
	dda.map.y = (int)(all->player_pos.y / TILE_SIZE);
	dda.delta_dist.x = fabs(TILE_SIZE / dda.ray_dir.x);
	dda.delta_dist.y = fabs(TILE_SIZE / dda.ray_dir.y);
	dda.hit = 0;
	dda.side = 0;
	calculate_step(all, &dda);
	dda_loop(&dda, all->map);
	check_wall_face(&raycast, all, &dda);
	if (dda.side == 0)
		raycast.perp_wall_dist = (dda.side_dist.x - dda.delta_dist.x);
	else
		raycast.perp_wall_dist = (dda.side_dist.y - dda.delta_dist.y);
	raycast.fish_eye_correction = raycast.perp_wall_dist
		* cos(angle - all->player_angle);
	raycast.dda = dda;
	draw_wall(all, &raycast, x);
}


// void	square(t_all *all, int x, int y, int color)
// {
// 	int	i;
// 	int	j;
// 	mlx_image_t	*square;

// 	i = 0;
// 	square = mlx_new_image(all->mlx, TILE_SIZE, TILE_SIZE);
// 	while (i < TILE_SIZE)
// 	{
// 		j = 0;
// 		while (j < TILE_SIZE)
// 		{
// 			if (i == 0 || i == TILE_SIZE - 1 || j == 0 || j == TILE_SIZE - 1)
// 				mlx_put_pixel(square, i, j, 0x000000);
// 			else
// 				mlx_put_pixel(square, i, j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (mlx_image_to_window(all->mlx, square, x, y) < 0)
// 		ft_all_exit(all, "mlx_image_to_window failed in square");
// }

// int	only_direction(char c)
// {
// 	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
// 		return (1);
// 	return (0);
// }

// void	draw_map(t_all *all)
// {
// 	int	i = 0;
// 	int	j = 0;

// 	while (all->map && all->map[i])
// 	{
// 		j = 0;
// 		while (all->map[i][j])
// 		{
// 			if (all->map[i][j] == '1')
// 				square(all, j * TILE_SIZE, i * TILE_SIZE, all->color_c);
// 			else if (all->map[i][j] == '0')
// 				square(all, j * TILE_SIZE, i * TILE_SIZE, all->color_f);
// 			j++;
// 		}
// 		i++;
// 	}
// 	// mlx_image_to_window(all->mlx, all->img, 0, 0);
// }
