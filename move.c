/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:01:23 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/01 17:18:29 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_rotate(t_mlx *mlx, int dir)
{
	int i;
	double angle = 0.01;

	i = 0;
	while (i < 2)
	{
		double tx = mlx->points[i].x - mlx->player->x;
		double ty = mlx->points[i].y - mlx->player->y;

		double tz = tx * cos(mlx->player->pov) + ty * sin(mlx->player->pov);
		tx = tx * sin(mlx->player->pov) - ty * cos(mlx->player->pov);

		mlx->points[i].x = mlx->player->x - tx;
		mlx->points[i].y = mlx->player->y - tz;

		i++;
	}
}

void	ft_view(t_mlx *mlx, int dir)
{
	ft_reset_img(mlx);

	mlx->player->pov += 0.1 * dir;
	// (mlx->player->pov > 6.28) ? mlx->player->pov = 0 : 1;
	// (mlx->player->pov < -6.28) ? mlx->player->pov = 0 : 1;
	printf("pov %f\n", mlx->player->pov);

	mlx->player->dir_xo = mlx->player->x + (mlx->player->dir_xo - mlx->player->x) * cos(mlx->player->pov) - (mlx->player->dir_yo - mlx->player->y) * sin(mlx->player->pov);
	mlx->player->dir_yo = mlx->player->y + (mlx->player->dir_xo - mlx->player->x) * sin(mlx->player->pov) + (mlx->player->dir_yo - mlx->player->y) * cos(mlx->player->pov);

	mlx->player->dir_x = mlx->player->x + (mlx->player->dir_x - mlx->player->x) * cos(mlx->player->pov) - (mlx->player->dir_y - mlx->player->y) * sin(mlx->player->pov);
	mlx->player->dir_y = mlx->player->y + (mlx->player->dir_x - mlx->player->x) * sin(mlx->player->pov) + (mlx->player->dir_y - mlx->player->y) * cos(mlx->player->pov);

	// mlx->player->x += sin(mlx->player->pov);
	// mlx->player->y += cos(mlx->player->pov);

	ft_view_dir(mlx);

	ft_rotate(mlx, dir);

	ft_draw_all(mlx);
}

void	ft_player_move(t_mlx *mlx, int dir)
{
	ft_reset_img(mlx);

	mlx->player->x += cos(mlx->player->pov) * 5 * dir;
	mlx->player->y += sin(mlx->player->pov) * 5 * dir;

	ft_view_dir(mlx);	

	ft_draw_all(mlx);
}
