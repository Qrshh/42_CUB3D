#include "cub3d.h"

int check_extension(char *str)
{
	int i;

	i = ft_strlen(str) -1;
	if(str[i - 3] != '.' && str[i - 2] != 'c' && str[i - 1] != 'u' && str[i] != 'b')
		return (1);
	return (0);
}

int check_opening(char *file, int *fd)
{
	*fd = open(file, O_DIRECTORY);
	if(*fd != -1 && *fd > 2)
		return(close(*fd), 1);
	*fd = open(file, O_RDONLY);
	if(*fd == -1)
		return(1);
	return(0);
}

int take_info_map(t_parse *parsing)
{
	char *line;
	int i;

	i = 0;
	while(i < 128)
		parsing->tab[i] = NULL;
	line = get_next_line(parsing->fd_map);
	i = 0;
	while(line != NULL)
	{
		parsing->tab[i] = ft_strdup(line);
		if(!parsing->tab[i])
			return(free_double(parsing->tab), \
			close(parsing->fd_map) ,1);
		free(line);
		line = get_next_line(parsing->fd_map);
		i++;
	}
	close(parsing->fd_map);
	return (0);
}