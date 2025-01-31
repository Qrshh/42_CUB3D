/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:38 by abesneux          #+#    #+#             */
/*   Updated: 2025/01/31 18:58:38 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <unistd.h>

# define HEIGHT 720
# define WIDTH 1200

typedef struct s_info
{
	// position et direction du player
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	// map
	char	**map;
	// textures
	char	*texture_path[4];
	char	*textures[4];
	// sol et plafond
	int		floor_color;
	int		ceiling_color;
	// MLX
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_info;

typedef struct s_parse
{
	int		fd_map;
	int		fd_texture;
}			t_parse;

// PARSING
int			check_extension(char *str);
int			check_opening(char *file, int *fd);
int			take_info_map(t_info *info, int fd_map);
int			init_infos(t_info *info);
int			find_player_position(t_info *info);

// UTILS
void		exit_error(char *str);
void		free_double(char **tab);

#endif