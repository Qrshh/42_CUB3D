/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:12:46 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/13 02:11:52 by mosmont          ###   ########.fr       */
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
	draw_minimap(all);
}

void	calculate_ray(t_all *all, t_raycast *raycast, t_coord pos_ray, double angle)
{
	raycast->pos_ray = pos_ray;
	raycast->distance = sqrt(pow(pos_ray.x - all->player_pos.x, 2)
		+ pow(pos_ray.y - all->player_pos.y, 2));
	raycast->fish_eye_correction = raycast->distance * cos(angle - all->player_angle);
	raycast->projected_wall_height = (WIDTH / 2) / tan(FOV / 2);
	raycast->wall_height = (TILE_SIZE * raycast->projected_wall_height) / raycast->fish_eye_correction;
	raycast->y_start = (HEIGHT / 2) - (raycast->wall_height / 2);
	raycast->y_end = (HEIGHT / 2) + (raycast->wall_height / 2);
	// printf("raycast->y_start = %d\n", raycast->y_start);
	// printf("raycast->y_end = %d\n", raycast->y_end);
}

int	check_wall_face(t_all *all, t_raycast *raycast)
{
	if (fmod(raycast->pos_ray.x, TILE_SIZE)
		> fmod(raycast->pos_ray.y, TILE_SIZE))
	{
		if (all->plane_pos.x > 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (all->plane_pos.y < 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}



void	calcul_tex(mlx_texture_t **texture_tab, int wall_face, t_raycast *raycast, int y)
{
	double	wall_x;
	// int		d;

	// printf("raycast->pos_ray.x = %f\n", raycast->pos_ray.x);
	// printf("raycast->pos_ray.y = %f\n", raycast->pos_ray.y);
	// 
	// raycast->texture_coord.x = fmodf(raycast->pos_ray.x * (texture_tab[wall_face]->width / TILE_SIZE), texture_tab[wall_face]->width);
	if (wall_face == 0 || wall_face == 1)
		wall_x = (fmod(raycast->pos_ray.x, TILE_SIZE) / TILE_SIZE);
	else
		wall_x = (fmod(raycast->pos_ray.y, TILE_SIZE) / TILE_SIZE);
	// printf("Wall_x = %f\n", wall_x);
	// printf("y = %d\n", y);
	(void)y;
	raycast->texture_coord.x = (wall_x * texture_tab[wall_face]->width);
	// d = (y - raycast->y_start) * 256 - HEIGHT * 128 + raycast->wall_height * 128;
	raycast->texture_coord.y = (y - raycast->y_start) * (texture_tab[wall_face]->height / raycast->wall_height);
	// if (raycast->texture_coord.y < 0)
	// 	raycast->texture_coord.y = 0;
	// printf("raycast->texture_coord.x = %f\n", raycast->texture_coord.x);
	// printf("raycast->texture_coord.y = %f\n\n", raycast->texture_coord.y);
}

void	calculate_color(mlx_texture_t **texture_tab, int wall_face, t_raycast *raycast)
{
	// if (raycast->texture_coord.x < 0) 
	// 	raycast->texture_coord.x = 0;
    // if (raycast->texture_coord.y < 0) 
	// 	raycast->texture_coord.y = 0;
    // if (raycast->texture_coord.x >= texture_tab[wall_face]->width) 
	// 	raycast->texture_coord.x = texture_tab[wall_face]->width - 1;
    // if (raycast->texture_coord.y >= texture_tab[wall_face]->height)
	// 	raycast->texture_coord.y = texture_tab[wall_face]->height - 1;
	raycast->tex_index = ((((int)raycast->texture_coord.y * (int)texture_tab[wall_face]->width + (int)raycast->texture_coord.x)
							)* texture_tab[wall_face]->bytes_per_pixel);
	// printf("raycast->tex_index = %d\n", raycast->tex_index);
	raycast->pixel = &texture_tab[wall_face]->pixels[raycast->tex_index];
	raycast->color = (raycast->pixel[0] << 24) | (raycast->pixel[1] << 16) | (raycast->pixel[2] << 8) | raycast->pixel[3];
}

void	draw_wall(t_all *all, t_coord pos_ray, double angle, int x)
{
	t_raycast	raycast;
	int			wall_face;
	int			y;

	calculate_ray(all, &raycast, pos_ray, angle);
	wall_face = check_wall_face(all, &raycast);
	// printf("wall_face = %d\n", wall_face);
	// if (raycast.y_start < 0)
	// 	raycast.y_start = 0;
	// if (raycast.y_end >= HEIGHT)
	// 	raycast.y_end = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < raycast.y_start)
			mlx_put_pixel(all->wall_img, x, y, all->color_c);
		else if (y > raycast.y_end)
			mlx_put_pixel(all->wall_img, x, y, all->color_f);
		else
		{
			calcul_tex(all->tab_textures, wall_face, &raycast, y);
			calculate_color(all->tab_textures, wall_face, &raycast);
			mlx_put_pixel(all->wall_img, x, y, raycast.color);
		}
		y++;
	}
}


// FOR DEBUG
// mlx_put_pixel(all->ray_img, (int)player_coord.x, (int)player_coord.y, all->color_c);
void	draw_ray(t_all *all, double angle, int x)
{
	t_coord	player_coord;
	t_coord	ray_coord;
	int		map_x;
	int		map_y;
	int		i;
	(void)x;

	player_coord.x = all->player_pos.x;
	player_coord.y = all->player_pos.y;
	ray_coord.x = cos(angle);
	ray_coord.y = sin(angle);
	i = -1;
	while (++i < RENDER_DISTANCE)
	{
		player_coord.x += ray_coord.x;
		player_coord.y += ray_coord.y;
		map_x = (int)(player_coord.x / TILE_SIZE);
		map_y = (int)(player_coord.y / TILE_SIZE);
		if (all->map[map_y][map_x] == '1')
			break ;
		// mlx_put_pixel(all->ray_img, (int)player_coord.x, (int)player_coord.y, all->color_c);
	}
	draw_wall(all, player_coord, angle, x);
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
