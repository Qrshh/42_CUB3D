/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_toggle_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:13:14 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/17 21:14:29 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void toggle_nightvision(t_all *all)
{
    all->night_vision = !all->night_vision;
}