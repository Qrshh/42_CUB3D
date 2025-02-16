/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:12:46 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/16 02:10:36 by mosmont          ###   ########.fr       */
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
	while (angle < end_angle && x < WIDTH)
	{
		draw_ray(all, angle, x);
		angle += step;
		x++;
	}
	// draw_ray(all, 3 * M_PI / 2, WIDTH / 2);
	draw_minimap(all);
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



void	calcul_tex(t_all *all, t_raycast *raycast, int y)
{
	double wall_x;

	if (raycast->dda.side == 0)
		wall_x = fmod((all->player_pos.y + raycast->perp_wall_dist * raycast->dda.ray_dir.y), TILE_SIZE) / TILE_SIZE;
	else
		wall_x = fmod((all->player_pos.x + raycast->perp_wall_dist * raycast->dda.ray_dir.x), TILE_SIZE) / TILE_SIZE;
	// printf("wall x %f\n", wall_x);
	raycast->texture_coord.x = (wall_x * all->tab_textures[raycast->wall_face]->width);
	// if (raycast->texture_coord.x < 0)
    // 	raycast->texture_coord.x = 0;
	// if (raycast->texture_coord.x >= all->tab_textures[raycast->wall_face]->width)
	// 	raycast->texture_coord.x = all->tab_textures[raycast->wall_face]->width - 1;
	raycast->texture_coord.y = ((y - raycast->y_start) * all->tab_textures[raycast->wall_face]->height / raycast->wall_height);
	// if (raycast->texture_coord.y < 0)
    // 	raycast->texture_coord.y = 0;
	if (raycast->texture_coord.y >= (int)all->tab_textures[raycast->wall_face]->height)
		raycast->texture_coord.y = (int)all->tab_textures[raycast->wall_face]->height - 1;
	
	
	// FOR DEBUG
	// int x_center = (int)(all->player_pos.x + raycast->perp_wall_dist * raycast->dda.ray_dir.x);
	// int y_center = (int)(all->player_pos.y + raycast->perp_wall_dist * raycast->dda.ray_dir.y);
	// for (int x_offset = -1; x_offset <= 1; x_offset++) {
	// 	for (int y_offset = -1; y_offset <= 1; y_offset++) {
	// 		int x = x_center + x_offset;
	// 		int y = y_center + y_offset;
			
	// 		// Vérifier les limites de l'image
	// 		mlx_put_pixel(all->wall_img, x, y, 0xFF0000FF); // Rouge opaque
	// 	}
	// }
}

void	calculate_color(mlx_texture_t **texture_tab, t_raycast *raycast)
{
	raycast->tex_index = ((((int)raycast->texture_coord.y * (int)texture_tab[raycast->wall_face]->width + (int)raycast->texture_coord.x)
							)* texture_tab[raycast->wall_face]->bytes_per_pixel);
	// printf("raycast->tex_index = %d\n", raycast->tex_index);
	raycast->pixel = &texture_tab[raycast->wall_face]->pixels[raycast->tex_index];
	raycast->color = (raycast->pixel[0] << 24) | (raycast->pixel[1] << 16) | (raycast->pixel[2] << 8) | raycast->pixel[3];
}

void calculate_ray(t_raycast *raycast)
{
	raycast->wall_height = (int)(TILE_SIZE * HEIGHT / raycast->perp_wall_dist);
	if (raycast->wall_height > HEIGHT)
		raycast->wall_height = HEIGHT;
	raycast->y_start = -raycast->wall_height / 2 + HEIGHT / 2;
    if (raycast->y_start < 0)
        raycast->y_start = 0;

    raycast->y_end = raycast->wall_height / 2 + HEIGHT / 2;
    if (raycast->y_end >= HEIGHT)
        raycast->y_end = HEIGHT - 1;
}

void	draw_wall(t_all *all, t_raycast *raycast, int x)
{
	int			y;
	// int			wall_face;

	calculate_ray(raycast);
	// wall_face = check_wall_face(all, &raycast);
	// printf("wall_face = %d\n", wall_face);
	// if (raycast.y_start < 0)
	// 	raycast.y_start = 0;
	// if (raycast.y_end >= HEIGHT)
	// 	raycast.y_end = HEIGHT - 1;
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
			calculate_color(all->tab_textures, raycast);
			mlx_put_pixel(all->wall_img, x, y, raycast->color);
		}
		y++;
	}
}


// FOR DEBUG
// mlx_put_pixel(all->ray_img, (int)player_coord.x, (int)player_coord.y, all->color_c);
void    draw_ray(t_all *all, double angle, int x)
{
    t_dda       dda;
    t_raycast   raycast;

	dda.ray_dir.x = cos(angle);
    dda.ray_dir.y = sin(angle);
    dda.map.x = (int)(all->player_pos.x / TILE_SIZE);
    dda.map.y = (int)(all->player_pos.y / TILE_SIZE);
    dda.delta_dist.x = fabs(TILE_SIZE / dda.ray_dir.x);
    dda.delta_dist.y = fabs(TILE_SIZE / dda.ray_dir.y);
	if (dda.ray_dir.x < 0)
	{
		dda.step.x = -1;
		dda.side_dist.x = (all->player_pos.x - (dda.map.x * TILE_SIZE)) / fabs(dda.ray_dir.x);
	}
	else
	{
		dda.step.x = 1;
		dda.side_dist.x = ((dda.map.x + 1) * TILE_SIZE - all->player_pos.x) / fabs(dda.ray_dir.x);
	}

	if (dda.ray_dir.y < 0)
	{
		dda.step.y = -1;
		dda.side_dist.y = (all->player_pos.y - (dda.map.y * TILE_SIZE)) / fabs(dda.ray_dir.y);
	}
	else
	{
		dda.step.y = 1;
		dda.side_dist.y = ((dda.map.y + 1) * TILE_SIZE - all->player_pos.y) / fabs(dda.ray_dir.y);
	}
    dda.hit = 0;
    dda.side = 0;
    while (dda.hit == 0)
    {
        if (dda.side_dist.x < dda.side_dist.y)
        {
            dda.side_dist.x += dda.delta_dist.x;
            dda.map.x += dda.step.x;
            dda.side = 0;
        }
        else
        {
            dda.side_dist.y += dda.delta_dist.y;
            dda.map.y += dda.step.y;
            dda.side = 1;
        }
        if (all->map[dda.map.y][dda.map.x] == '1')
			dda.hit = 1;
	}
	if (dda.side == 0)
    {
        if (dda.ray_dir.x < 0)
            raycast.wall_face = WEST;
        else
            raycast.wall_face = EAST;
    }
    else
    {
        if (dda.ray_dir.y < 0)
            raycast.wall_face = NORTH;
        else
            raycast.wall_face = SOUTH;
    }
	if (dda.side == 0)
		raycast.perp_wall_dist = (dda.side_dist.x - dda.delta_dist.x);
	else
		raycast.perp_wall_dist = (dda.side_dist.y - dda.delta_dist.y);

	raycast.perp_wall_dist *= cos(angle - all->player_angle);
    raycast.dda = dda;
	draw_wall(all, &raycast, x);
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
				square(all, j * TILE_SIZE, i * TILE_SIZE, all->color_c);
			else if (all->map[i][j] == '0')
				square(all, j * TILE_SIZE, i * TILE_SIZE, all->color_f);
			j++;
		}
		i++;
	}
	// mlx_image_to_window(all->mlx, all->img, 0, 0);
}
