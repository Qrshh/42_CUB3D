/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:38 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/10 21:34:52 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080

# define MOV_SPEED 0.1
# define ROT_SPEED 0.05
# define TILE_SIZE 16

typedef struct s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_all
{
	t_coord			player_pos;
	t_coord			dir_pos;
	t_coord			plane_pos;
	int				starting_dir;
	char			**map;
	int				width_map;
	char			**infos;
	mlx_texture_t	*tab_textures[4];
	mlx_t			*mlx;
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

// UTILS
int					only_spaces(char *str);
void				exit_error(char *str);
void				ft_all_exit(t_all *all, char *str);
void				free_all(t_all *all);
void				free_tab(char **tab);

// RENDER
void				draw_map(t_all *all);

#endif