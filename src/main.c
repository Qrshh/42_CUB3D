#include "cub3d.h"

int main(int ac, char **av)
{
	t_info info;
	
	if(ac != 2)
		exit_error("Args Problem");
	if(check_extension(av[1]))
		exit_error("Wrong extension for the map");
	if(check_opening(av[1], &info.fd_map))
		exit_error("File is not opening");
}