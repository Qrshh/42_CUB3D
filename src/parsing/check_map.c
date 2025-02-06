/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:29:01 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/03 19:32:52 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int forbidden_char(char **map)
{
    int i;
    int j;
    int starting_pos;

    i = -1;
    starting_pos = 0;
    while(map[++i])
    {
        j = -1;
        while(map[i][++j])
        {
            if(ft_strchr("NEWS", map[i][j]))  
                starting_pos++;
        }
    }
    return(starting_pos != 1); //retourne 1 si starting pos est different de 1, sinon ca retourne 0
}

void check_valid_map(t_all **all)
{
    if(!(*all)->map)
        ft_all_exit(*all, "Map is invalid");
    if(!forbidden_char((*all)->map))
        ft_all_exit(*all, "Wrong char inside map");
    //check si la map est close ou pas
    //check si la starting pos pue la merde ou pas
}