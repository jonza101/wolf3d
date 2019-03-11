/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:20:31 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/11 19:53:24 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

void	ft_draw_circle(t_mlx *mlx, int xo, int yo, int color)
{
	int x = mlx->slider->radius;
	int y = 0;
	int radius_error = 1 - mlx->slider->radius;
	while (x >= y)
	{
		ft_image(mlx, x + xo, y + yo, color);
		ft_image(mlx, y + xo, x + yo, color);
		ft_image(mlx, -x + xo, y + yo, color);
		ft_image(mlx, -y + xo, x + yo, color);
		ft_image(mlx, -x + xo, -y + yo, color);
		ft_image(mlx, -y + xo, -x + yo, color);
		ft_image(mlx, x + xo, -y + yo, color);
		ft_image(mlx, y + xo, -x + yo, color);
		y++;
		if (radius_error < 0)
			radius_error += 2 * y + 1;
		else
		{
			x--;
			radius_error += 2 * (y - x + 1);
		}
	}
}
