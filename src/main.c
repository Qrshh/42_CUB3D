#include "cub3d.h"

int main(int ac, char **av)
{
	t_parse parse;
	t_info info;
	
	if(ac != 2)
		exit_error("Args Problem");
	if(check_extension(av[1]))
		exit_error("Wrong extension for the map");
	if(check_opening(av[1], &parse.fd_map))
		exit_error("File is not opening");
	if(take_info_map(&parse))
		exit_error("An error occured while taking the infos");
	//initialisation de tout ce dont on a besoin
	init_infos(&info);

	ft_printf("Perfect\n");
}