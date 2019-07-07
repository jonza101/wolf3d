/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 12:14:57 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/07 14:16:32 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_move_calc_tmp(t_mlx *mlx)
{
	if (mlx->player->wsad[2])
	{
		if (ft_walls_check(mlx->map, (int)(mlx->player->x -
					cosf(mlx->player->pov) * 0.5), (int)mlx->player->y))
			mlx->player->x -= cosf(mlx->player->pov) * 0.1;
		if (ft_walls_check(mlx->map, (int)mlx->player->x,
					(int)(mlx->player->y + sinf(mlx->player->pov) * 0.5)))
			mlx->player->y += sinf(mlx->player->pov) * 0.1;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
	}
	if (mlx->player->wsad[3])
	{
		if (ft_walls_check(mlx->map, (int)(mlx->player->x +
					cosf(mlx->player->pov) * 0.5), (int)mlx->player->y))
			mlx->player->x += cosf(mlx->player->pov) * 0.1;
		if (ft_walls_check(mlx->map, (int)mlx->player->x,
					(int)(mlx->player->y - sinf(mlx->player->pov) * 0.5)))
			mlx->player->y -= sinf(mlx->player->pov) * 0.1;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
	}
}

void	ft_move_calc(t_mlx *mlx)
{
	if (mlx->player->wsad[0])
	{
		if ((ft_walls_check(mlx->map, (int)(mlx->player->x +
					sinf(mlx->player->pov) * 0.5), (int)mlx->player->y)))
			mlx->player->x += sinf(mlx->player->pov) * 0.15;
		if (ft_walls_check(mlx->map, (int)mlx->player->x,
					(int)(mlx->player->y + cosf(mlx->player->pov) * 0.8)))
			mlx->player->y += cosf(mlx->player->pov) * 0.15;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
	}
	if (mlx->player->wsad[1])
	{
		if ((ft_walls_check(mlx->map, (int)(mlx->player->x -
					sinf(mlx->player->pov) * 0.5), (int)mlx->player->y)))
			mlx->player->x -= sinf(mlx->player->pov) * 0.1;
		if (ft_walls_check(mlx->map, (int)mlx->player->x,
					(int)(mlx->player->y - cosf(mlx->player->pov) * 0.8)))
			mlx->player->y -= cosf(mlx->player->pov) * 0.1;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
	}
	ft_move_calc_tmp(mlx);
}
