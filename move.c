/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:01:23 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/02/28 15:47:13 by zjeyne-l         ###   ########.fr       */
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


	mlx->player->dir_xo = mlx->player->x + (mlx->player->dir_xo - mlx->player->x) * cos(angle) - (mlx->player->dir_yo - mlx->player->y) * sin(angle);
	mlx->player->dir_yo = mlx->player->y + (mlx->player->dir_xo - mlx->player->x) * sin(angle) + (mlx->player->dir_yo - mlx->player->y) * cos(angle);

	mlx->player->dir_x = mlx->player->x + (mlx->player->dir_x - mlx->player->x) * cos(angle) - (mlx->player->dir_y - mlx->player->y) * sin(angle);
	mlx->player->dir_y = mlx->player->y + (mlx->player->dir_x - mlx->player->x) * sin(angle) + (mlx->player->dir_y - mlx->player->y) * cos(angle);


	ft_draw_all(mlx);
}

void	ft_player_move(t_mlx *mlx, int dir)
{
	int	angle_x;
	int angle_y;
	int error;

	angle_x = fabs(mlx->player->dir_x - mlx->player->dir_xo);
	angle_y = fabs(mlx->player->dir_y - mlx->player->dir_yo);
	error = angle_x - angle_y;

	ft_reset_img(mlx);

	if (error * 2 > -angle_y)
		mlx->player->x += 1 * dir;
	if (error * 2 < angle_x)
		mlx->player->y += 1 * dir;

	ft_view(mlx, 0);

	ft_draw_all(mlx);
}
