/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:55:55 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/03 13:00:31 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_ray_start(t_mlx *mlx)
{
	mlx->player->x = mlx->player->start_x;
	mlx->player->y = mlx->player->start_y;
	mlx->player->fov = 1.5708f;
	mlx->player->pov = -1.57;
	mlx->depth = 32;
	mlx->player->ammo = 0;
	mlx->player->score = 0;
	mlx->player->hp = 100;
}

void	ft_ray_cast(t_mlx *mlx)
{
	int x;
	int w;

	x = (W / THREAD) * (mlx->mlx_index % THREAD) - 1;
	w = (W / THREAD) * (mlx->mlx_index % THREAD) + (W / THREAD);
	while (++x < w)
	{
		ft_ray_iter_init(mlx, x);
		while (mlx->hit == 0 && mlx->dist_to_wall < mlx->depth)
			ft_hit_calc(mlx);
		mlx->ceiling = (double)(H / 2.0) - H /
						(double)mlx->dist_to_wall / mlx->player->fov;
		mlx->floor = H - mlx->ceiling;
		mlx->depth_buff[x] = mlx->dist_to_wall;
		ft_col_fill(mlx, x);
	}
}
