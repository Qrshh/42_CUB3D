/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:24:24 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/10 19:34:29 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_args(int ac, char **av)
{
	if (ac != 2)
		exit_error("Wrong number of arguments");
	if (check_format(av[1], ".cub"))
		exit_error("Wrong format");
}

void	check_file(t_all **all)
{
	int size;
	
	check_valid_map(all);
	size = -1;
	while((*all)->infos && (*all)->infos[++size])
	{
		if(size == 0)
			is_info_valid(all, (*all)->infos[size]);
		
	}
}

void	fill_tab(t_all **all, char *filename)
{
	char	*line;
	int		fd;
	int		flag;

	flag = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_all_exit(*all, "File could not be opened");
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_line_map(*all, line))
		{
			if (!only_spaces(line))
				flag = 1;
			if (flag)
			{
				if (line[0] == '\n')
				{
					free(line);
					continue ;
				}
				(*all)->map = add_line((*all)->map, line);
			}
		}
		else if (only_spaces(line))
			(*all)->infos = add_line((*all)->infos, line);
		free(line);
	}
	close(fd);
}

void	parsing(t_all **all, int ac, char **av)
{
	check_args(ac, av);
	init_ptr(all);
	fill_tab(all, av[1]);
	check_file(all);
}
