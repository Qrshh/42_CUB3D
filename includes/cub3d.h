#ifndef CUB3D_H
#define CUB3D_H

#include "Libft/libft.h"
#include <fcntl.h>
#include <unistd.h>


typedef struct s_info
{
	int fd_map;

}t_info;

//UTILS
int check_extension(char *str);
void exit_error(char *str);
int check_opening(char *str, int *fd);

#endif