/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_toggle_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:13:14 by abesneux          #+#    #+#             */
/*   Updated: 2025/02/17 21:24:20 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void toggle_nightvision(t_all *all)
{
    all->night_vision = !all->night_vision;
}