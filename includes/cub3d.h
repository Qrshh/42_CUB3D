/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:38 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/11 21:37:52 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# define WIDTH 500
# define HEIGHT 500

# define MOV_SPEED 0.5
# define ROT_SPEED 0.05
# define TILE_SIZE 16
# define COLLISION_MARGIN 5
# define FOV (70 * (M_PI / 180.0))

typedef struct s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_all
{
	t_coord			player_pos;
	double			player_angle;
	t_coord			plane_pos;
	int				starting_dir;
	char			**map;
	int				width_map;
	char			**infos;
	mlx_texture_t	*tab_textures[4];
	mlx_t			*mlx;
	int				f;
	int				c;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				color_c;
	int				color_f;
	mlx_image_t		*img;
	mlx_image_t		*player_img;
	mlx_image_t		*ray_img;
}					t_all;

// PARSING
void				parsing(t_all **all, int ac, char **av);
void				init_ptr(t_all **all);
void				check_args(int ac, char **av);
int					check_format(char *str, char *cmp);
int					is_line_map(t_all *all, char *line);
void				check_valid_map(t_all **all);
char				**add_line(char **tab, char *line);
int					is_allowed_char(char c);
void				is_info_valid(t_all **all, char *line);
void				update_count(t_all **all, char *id);
void				is_valid_color(t_all **all, char *line);
void				update_color(t_all **all, char *color, char id);
// UTILS
int					only_spaces(char *str);
void				exit_error(char *str);
void				ft_all_exit(t_all *all, char *str);
void				free_all(t_all *all);
void				free_tab(char **tab);

// RENDER
void				draw_map(t_all *all);
void				square(t_all *all, int x, int y, int color);
void				draw_ray(t_all *all, double angle);
void				draw_fov(t_all *all);

// PLAYER
void				init_player(t_all **all, int i, int j);
void				event_listener(void *param);
void				fov_mooves(void *param);

#endif