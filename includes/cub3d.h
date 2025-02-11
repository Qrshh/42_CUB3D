/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:38 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/11 22:04:38 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080

# define MOV_SPEED 5
# define ROT_SPEED 0.05
# define TILE_SIZE 64
# define FOV (70 * (M_PI / 180.0))

typedef struct s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_all
{
	t_coord			player_pos;
	double 			player_angle;
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
	mlx_image_t		*wall_img;
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
void				draw_ray(t_all *all, double offset_angle, int x);
void				draw_fov(t_all *all);


// PLAYER
void 				event_listener(void *param);


#endif