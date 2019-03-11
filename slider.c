/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:19:49 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/11 19:53:29 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_slider_line(t_mlx *mlx, int mouse_x)
{
	int x;
	int y;
	int xo;

	mlx->slider->x = mouse_x;
	y = mlx->slider->y - mlx->slider->height / 2;
	xo = mlx->slider->xo - mlx->slider->len;
	while (y < mlx->slider->y + mlx->slider->height / 2)
	{
		x = xo;
		while (x < mlx->slider->xo)
		{
			ft_image(mlx, x, y, 0x808080);
			x++;
		}
		y++;
	}
	ft_draw_circle(mlx, mlx->slider->x, mlx->slider->y, 0xFF00FF);
}
