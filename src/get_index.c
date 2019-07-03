/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:52:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/03 13:00:10 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int		ft_get_tile_index_t(char c)
{
	if (c == EAGLE)
		return (6);
	else if (c == FLAG)
		return (7);
	else if (c == GH)
		return (8);
	else if (c == WW)
		return (9);
	else if (c == WEAGLE)
		return (10);
	else if (c == WH)
		return (11);
	else if (c == BUNKWALL)
		return (12);
	return (-1);
}

int		ft_get_tile_index(char c)
{
	if (c == BW1)
		return (0);
	else if (c == BW2)
		return (1);
	else if (c == CELL)
		return (2);
	else if (c == SCELL)
		return (3);
	else if (c == GB1)
		return (4);
	else if (c == GB2)
		return (5);
	return (ft_get_tile_index_t(c));
}

int		ft_get_obj_index_tmp(char c)
{
	if (c == FLAGPOLE)
		return (17);
	else if (c == GBARREL)
		return (18);
	else if (c == BUBBLER)
		return (19);
	else if (c == S_SKELETON)
		return (20);
	else if (c == K_STUFF)
		return (21);
	else if (c == B_BONES)
		return (22);
	else if (c == PILLAR)
		return (23);
	else if (c == CAGE)
		return (24);
	else if (c == S_CAGE)
		return (25);
	return (-1);
}

int		ft_get_obj_index_t(char c)
{
	if (c == FWELL)
		return (8);
	else if (c == EWELL)
		return (9);
	else if (c == DPOT)
		return (10);
	else if (c == DEAD)
		return (11);
	else if (c == KNIGHT)
		return (12);
	else if (c == VASE)
		return (13);
	else if (c == TCHAIRS)
		return (14);
	else if (c == BUSH)
		return (15);
	else if (c == FLAMP)
		return (16);
	return (ft_get_obj_index_tmp(c));
}

int		ft_get_obj_index(char c)
{
	if (c == SKELETON)
		return (0);
	else if (c == CLAMP)
		return (1);
	else if (c == BONES)
		return (2);
	else if (c == CHAND)
		return (3);
	else if (c == TREE)
		return (4);
	else if (c == PUDDLE)
		return (5);
	else if (c == BARREL)
		return (6);
	else if (c == TABLE)
		return (7);
	return (ft_get_obj_index_t(c));
}
