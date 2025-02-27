/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:38 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/20 00:46:04 by mosmont          ###   ########.fr       */
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

# define WIDTH 1000
# define HEIGHT 800

# define MOV_SPEED 2
# define BIG_SPEED 2
# define ROT_SPEED 0.05
# define TILE_SIZE 64
# define COLL_MARG 5
# define SENS 0.001
# define FOV 66

# define NB_SPRITE_TEX 1

# define DIST_LIGHT 0.005

# define NB_TEXT 5

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

typedef struct s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_coord_int
{
	int				x;
	int				y;
}					t_coord_int;

typedef struct s_rgb
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_rgb;

typedef struct s_dda
{
	t_coord			ray_dir;
	t_coord			side_dist;
	t_coord			delta_dist;
	t_coord			step;
	t_coord_int		map;
	int				hit;
	int				side;
}					t_dda;

typedef struct s_flash_light
{
	t_coord			player_dir;
	double			dst_factor;
	double			ray_dir_norm;
	double			player_dir_norm;
	double			scalar_product;
	double			angle_factor;
	double			falloff;
	double			light_factor;
}					t_flash_light;

typedef struct s_raycast
{
	t_coord			pos_ray;
	double			distance;
	int				wall_height;
	double			fish_eye;
	double			projected_wall_height;
	int				y_start;
	int				y_end;
	t_coord_int		texture_coord;
	int				tex_index;
	uint8_t			*pixel;
	int				color;
	int				hit_vertical;
	int				step_x;
	int				step_y;
	double			perp_wall_dist;
	int				wall_face;
	t_dda			dda;
}					t_raycast;

typedef struct s_sprite
{
	double			x;
	double			y;
	int				texture_id;
	double			distance;
}					t_sprite;

typedef struct s_all
{
	double			fov;
	t_coord			player_pos;
	double			player_angle;
	int				starting_dir;
	char			**map;
	int				width_map;
	char			**infos;
	mlx_texture_t	*tab_textures[NB_TEXT];
	mlx_t			*mlx;
	int				f;
	int				c;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				d;
	int				color_c;
	int				color_f;
	mlx_image_t		*minimap_img;
	mlx_image_t		*wall_img;
	bool			minimap_visible;
	bool			fov_mouse;
	bool			sprint;
	bool			night_vision;
	mlx_image_t		*text_img;
	t_raycast		*raycast;
}					t_all;

// PARSING
void				parsing(t_all **all, int ac, char **av);
void				init_ptr(t_all **all);
void				check_args(int ac, char **av);
int					check_format(char *str, char *cmp);
int					is_line_map(t_all *all, char *line, int fd);
void				check_valid_map(t_all **all);
char				**add_line(char **tab, char *line);
int					is_allowed_char(char c);
void				is_info_valid(t_all **all, char *line);
void				update_count(t_all **all, char *id);
void				is_valid_color(t_all **all, char *line);
void				update_color(t_all **all, char *color, char id);
void				adding_line(t_all **all, int fd, int flag);
// UTILS
int					only_spaces(char *str);
int					ft_isspace(char c);
int					is_border(int i, int j, int height, int len);
int					is_invalid_space(char **map, int i, int j, int height);
void				exit_error(char *str);
void				ft_all_exit(t_all *all, char *str);
void				free_all(t_all *all);
void				free_tab(char **tab);

// RENDER
void				draw_ray(t_all *all, double offset_angle, int x);
void				draw_fov(t_all *all);
void				draw_minimap(t_all *all);

void				calculate_color(mlx_texture_t **texture_tab,
						t_raycast *raycast, double player_angle,
						bool night_vision);
void				calcul_tex(t_all *all, t_raycast *raycast, int y);
void				check_wall_face(t_raycast *raycast, t_all *all, t_dda *dda);

void				dda_loop(t_dda *dda, char **map);
void				calculate_step(t_all *all, t_dda *dda);

// DYNAMIC_LIGHT
int					get_pixel_color(t_raycast *raycast, bool night_vision,
						double player_angle);

// UTILS RENDER
void				refresh_image(mlx_t *mlx, mlx_image_t **image);

// PLAYER
void				init_player(t_all **all, int i, int j);
void				moove_fw_bw(void *param);
void				moove_left_right(void *param);
void				fov_mooves(void *param);
void				toggle(mlx_key_data_t keydata, void *param);
void				mouse_moove(double x_pos, double y_pos, void *param);
void				toggle_nightvision(t_all *all);
void				init_nightvision_text(t_all *all);

void				move_forward(t_all *all);
void				move_backward(t_all *all);
void				move_right(t_all *all);
void				move_left(t_all *all);

#endif