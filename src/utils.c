#include "cub3d.h"

int check_extension(char *str)
{
	int i;

	i = ft_strlen(str) -1;
	if(str[i - 3] != '.' && str[i - 2] != 'c' && str[i - 1] != 'u' && str[i] != 'b')
		return (1);
	return (0);
}

int check_opening(char *str, int *fd)
{
	*fd = open(str, O_DIRECTORY);
	if(*fd != -1 && *fd > 2)
		return(close(*fd), 1);
	*fd = open(str, O_RDONLY);
	if(*fd == -1)
		return(1);
	return(0);
}

void exit_error(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}