/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:42:48 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/02/28 15:28:46 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_reset_img(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx_clear_window(mlx->mlx, mlx->win);
}

void	ft_draw_all(t_mlx *mlx)
{
	ft_draw_line(mlx, mlx->points[0].x, mlx->points[0].y, mlx->points[1].x, mlx->points[1].y, 0xFF00FF);
	ft_image(mlx, mlx->player->x, mlx->player->y, 0xFF00FF);
	ft_draw_line(mlx, mlx->player->dir_xo, mlx->player->dir_yo, mlx->player->dir_x, mlx->player->dir_y, 0xFFFFFF);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	ft_image(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < W && y >= 0 && y < H)
		mlx->data[x + y * W] = mlx_get_color_value(mlx->mlx, color);
}

void	ft_draw_line_start(t_mlx *mlx, int xo, int yo, int x, int y, int *delta_x, int *delta_y)
{
	if (x < xo)
		*delta_x = -1;
	else
		*delta_x = 1;
	if (y < yo)
		*delta_y = -1;
	else
		*delta_y = 1;
}

void	ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color)
{
	int angle_x;
	int angle_y;
	int delta_x;
	int delta_y;
	int error;

	angle_x = abs(x - xo);
	angle_y = abs(y - yo);
	error = angle_x - angle_y;
	ft_draw_line_start(mlx, xo, yo, x, y, &delta_x, &delta_y);
	ft_image(mlx, x, y, color);
	while (xo != x || yo != y)
	{
		ft_image(mlx, xo, yo, color);
		if (error * 2 > -angle_y)
		{
			error -= angle_y;
			xo += delta_x;
		}
		else if (error * 2 < angle_x)
		{
			error += angle_x;
			yo += delta_y;
		}
		else
			break ;
	}
}
