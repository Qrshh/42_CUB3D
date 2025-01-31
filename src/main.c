/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:20:31 by abesneux          #+#    #+#             */
/*   Updated: 2025/01/31 20:10:06 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_parse	parse;
	t_info	info;

	if (ac != 2)
		exit_error("Args Problem");
	if (check_extension(av[1]))
		exit_error("Wrong extension for the map");
	if (check_opening(av[1], &parse.fd_map))
		exit_error("File is not opening");
	if (init_infos(&info))
		exit_error("an error occured while initalizing the infos");
	if (take_info_map(&info, parse.fd_map))
		exit_error("An error occured while taking the infos");
	//fonction qui permet de check tout ce qu'il faut pour la map psk la je manque de trop de truc
	if (find_player_position(&info))
		return (1);
	ft_printf("Perfect\n");
	close(parse.fd_map);
	free_double(info.map);
	return (0);
}
