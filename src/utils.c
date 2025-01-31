#include "cub3d.h"

void free_double(char **tab)
{
    int i;

    i = 0;
    if(!tab)
        return ;
    while(tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void exit_error(char *str)
{
	ft_printf("Error\n");
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}