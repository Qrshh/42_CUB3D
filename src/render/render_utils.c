/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:18:55 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/17 00:25:41 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	refresh_image(mlx_t *mlx, mlx_image_t **image)
{
	if (!*image)
	{
		*image = mlx_new_image(mlx, WIDTH, HEIGHT);
		mlx_image_to_window(mlx, *image, 0, 0);
	}
	else
		ft_bzero((*image)->pixels, WIDTH * HEIGHT * 4);
}