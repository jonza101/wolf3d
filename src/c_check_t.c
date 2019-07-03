/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:00:39 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/03 12:59:47 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int		ft_walls_check(char **map, int player_x, int player_y)
{
	if (map[player_y][player_x] == SPACE
			|| map[player_y][player_x] == AMMO
			|| map[player_y][player_x] == CROSS
			|| map[player_y][player_x] == CUP
			|| map[player_y][player_x] == CROWN
			|| map[player_y][player_x] == CHEST
			|| map[player_y][player_x] == FOOD
			|| map[player_y][player_x] == DFOOD
			|| map[player_y][player_x] == MEDKIT)
		return (1);
	return (0);
}
