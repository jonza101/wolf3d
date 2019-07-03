/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:58:42 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/03 13:06:00 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int		ft_cobj_check(char c)
{
	if (c == AMMO || c == CROSS || c == CUP
			|| c == CROWN || c == CHEST || c == FOOD
			|| c == DFOOD || c == MEDKIT)
		return (1);
	return (0);
}

int		ft_is_obj_phys(char c)
{
	if (c == TREE || c == BARREL || c == TABLE
			|| c == FWELL || c == EWELL || c == KNIGHT
			|| c == VASE || c == TCHAIRS || c == BUSH
			|| c == FLAMP || c == FLAGPOLE || c == GBARREL
			|| c == BUBBLER || c == S_SKELETON || c == PILLAR
			|| c == CAGE || c == S_CAGE)
		return (1);
	return (0);
}

int		ft_obj_check_c(char c)
{
	if (c == SKELETON || c == CLAMP || c == BONES
			|| c == CHAND || c == TREE || c == PUDDLE
			|| c == BARREL || c == TABLE || c == FWELL
			|| c == EWELL || c == DPOT || c == DEAD
			|| c == KNIGHT || c == VASE || c == TCHAIRS
			|| c == BUSH || c == FLAMP || c == FLAGPOLE
			|| c == GBARREL || c == BUBBLER || c == S_SKELETON
			|| c == K_STUFF || c == B_BONES || c == PILLAR
			|| c == CAGE || c == S_CAGE)
		return (1);
	return (0);
}

void	ft_obj_check(t_mlx *mlx, char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == SKELETON || line[i] == CLAMP
				|| line[i] == BONES || line[i] == CHAND
				|| line[i] == TREE || line[i] == PUDDLE
				|| line[i] == BARREL || line[i] == TABLE
				|| line[i] == FWELL || line[i] == EWELL
				|| line[i] == DPOT || line[i] == DEAD
				|| line[i] == KNIGHT || line[i] == VASE
				|| line[i] == TCHAIRS || line[i] == BUSH
				|| line[i] == FLAMP || line[i] == FLAGPOLE
				|| line[i] == GBARREL || line[i] == BUBBLER
				|| line[i] == S_SKELETON || line[i] == K_STUFF
				|| line[i] == B_BONES || line[i] == PILLAR
				|| line[i] == CAGE || line[i] == S_CAGE)
			mlx->obj_count++;
		if (line[i] == AMMO || line[i] == CROSS
				|| line[i] == CUP || line[i] == CROWN
				|| line[i] == CHEST || line[i] == FOOD
				|| line[i] == DFOOD || line[i] == MEDKIT)
			mlx->cobj_count++;
	}
}

int		ft_tiles_check(char **map, int p_x, int p_y)
{
	if (map[p_y][p_x] == SPACE || map[p_y][p_x] == TREE
			|| map[p_y][p_x] == BARREL || map[p_y][p_x] == TABLE
			|| map[p_y][p_x] == FWELL || map[p_y][p_x] == EWELL
			|| map[p_y][p_x] == AMMO || map[p_y][p_x] == CROSS
			|| map[p_y][p_x] == CUP || map[p_y][p_x] == CROWN
			|| map[p_y][p_x] == CHEST || map[p_y][p_x] == KNIGHT
			|| map[p_y][p_x] == VASE || map[p_y][p_x] == TCHAIRS
			|| map[p_y][p_x] == BUSH || map[p_y][p_x] == FLAMP
			|| map[p_y][p_x] == FLAGPOLE || map[p_y][p_x] == GBARREL
			|| map[p_y][p_x] == FOOD || map[p_y][p_x] == DFOOD
			|| map[p_y][p_x] == MEDKIT || map[p_y][p_x] == BUBBLER
			|| map[p_y][p_x] == S_SKELETON || map[p_y][p_x] == PILLAR
			|| map[p_y][p_x] == CAGE || map[p_y][p_x] == S_CAGE)
		return (0);
	return (1);
}
