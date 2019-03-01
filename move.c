/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:01:23 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/01 14:25:26 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_rotate(t_mlx *mlx)
{
	int i;
	double angle = 0.01;

	i = 0;
	while (i < 2)
	{
		double tx = mlx->points[i].x - mlx->player->dir_x;
		double ty = mlx->points[i].y - mlx->player->dir_y;

		double zx = tx * cos(angle) + ty * sin(angle);
		tx = tx * sin(angle) - ty * cos(angle);

		mlx->points[i].x = mlx->points[i].x - tx;
		mlx->points[i].y = mlx->points[i].y - ty;

		i++;
	}
}

void	ft_view(t_mlx *mlx, int dir)
{
	double angle;

	angle = 0.05 * dir;

	ft_reset_img(mlx);

	// mlx->player->pov -= angle * 180 / M_PI;
	// (mlx->player->pov > 359) ? mlx->player->pov = 0 : 1;
	// (mlx->player->pov < 0) ? mlx->player->pov = 359 : 1;
	// printf("pov %f\n", mlx->player->pov);

	mlx->player->pov += 0.1 * dir;
	printf("pov %f\n", mlx->player->pov);

	mlx->player->dir_xo = mlx->player->x + (mlx->player->dir_xo - mlx->player->x) * cos(mlx->player->pov) - (mlx->player->dir_yo - mlx->player->y) * sin(mlx->player->pov);
	mlx->player->dir_yo = mlx->player->y + (mlx->player->dir_xo - mlx->player->x) * sin(mlx->player->pov) + (mlx->player->dir_yo - mlx->player->y) * cos(mlx->player->pov);

	mlx->player->dir_x = mlx->player->x + (mlx->player->dir_x - mlx->player->x) * cos(mlx->player->pov) - (mlx->player->dir_y - mlx->player->y) * sin(mlx->player->pov);
	mlx->player->dir_y = mlx->player->y + (mlx->player->dir_x - mlx->player->x) * sin(mlx->player->pov) + (mlx->player->dir_y - mlx->player->y) * cos(mlx->player->pov);

	ft_view_dir(mlx);

	ft_draw_all(mlx);
}

void	ft_player_move(t_mlx *mlx, int dir)
{
	ft_reset_img(mlx);

	mlx->player->x += cos(mlx->player->pov) * 5;
	mlx->player->y += sin(mlx->player->pov) * 5;

	ft_view_dir(mlx);	

	ft_draw_all(mlx);
}
