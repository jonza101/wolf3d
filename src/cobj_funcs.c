/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cobj_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:24:29 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/20 15:02:51 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_cobj_tmp_hp(t_mlx *mlx, int p_x, int p_y)
{
	if (mlx->cobjs->is == 2)
		mlx->player->hp += 10;
	else if (mlx->cobjs->is == 3)
		mlx->player->hp += 4;
	else if (mlx->cobjs->is == 4)
		mlx->player->hp += 25;
	(mlx->player->hp > 100) ? mlx->player->hp = 100 : 1;
	mlx->map[p_y][p_x] = SPACE;
}

void	ft_cobj_t(t_mlx *mlx, int p_x, int p_y, t_cobj *tmp)
{
	if (mlx->cobjs->is == 0)
	{
		mlx->player->ammo += 5;
		mlx->map[p_y][p_x] = SPACE;
	}
	else if (mlx->cobjs->is == 1)
	{
		mlx->player->score += 100;
		mlx->map[p_y][p_x] = SPACE;
	}
	else if (mlx->player->hp < 100)
	{
		ft_cobj_tmp_hp(mlx, p_x, p_y);
	}
	else if (mlx->player->hp == 100)
	{
		mlx->cobj_f = 1;
		mlx->cobjs = tmp;
	}
}
