#ifndef CUB3D_H
#define CUB3D_H

#include "Libft/libft.h"
#include <fcntl.h>
#include <unistd.h>


#define HEIGHT 720
#define WIDTH 1200

typedef struct s_info
{
	int pos_x;
	int pos_y;


}t_info;

typedef struct s_parse
{
	int fd_map;
	int fd_texture;
	char *tab[128];
}t_parse;

// PARSING 
int check_extension(char *str);
int check_opening(char *file, int *fd);
int take_info_map(t_parse *parsing);
int init_infos(t_info *info);

//UTILS
void exit_error(char *str);
void free_double(char **tab);

#endif