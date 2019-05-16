/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:20:31 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/16 19:34:56 by zjeyne-l         ###   ########.fr       */
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

void	ft_draw_cross(t_mlx *mlx )
{
	int i;

	i = W / 2 - 2;
	while (i <= W / 2 + 2)
	{
		ft_image(mlx, i, H / 2, 0xFFFFFF);
		i++;
	}
	i = H / 2 - 2;
	while (i <= H / 2 + 2)
	{
		ft_image(mlx, W / 2, i, 0xFFFFFF);
		i++;
	}
}

void	ft_draw_interface(t_mlx *mlx)
{
	char *ammo_str;
	char *score_str;
	char *hp_str;

	ammo_str = ft_strdup(ft_itoa(mlx->player->ammo));
	score_str = ft_strdup(ft_itoa(mlx->player->score));
	hp_str = ft_strdup(ft_itoa(mlx->player->hp));

	ammo_str = ft_strjoin("Ammo: ", ammo_str);
	score_str = ft_strjoin("Score: ", score_str);
	hp_str = ft_strjoin("Health: ", hp_str);

	mlx_string_put(mlx->mlx, mlx->win, 20, H - 40, 0xFFFFFF, ammo_str);
	mlx_string_put(mlx->mlx, mlx->win, 20, H - 20, 0xFFFFFF, score_str);
	mlx_string_put(mlx->mlx, mlx->win, 20, H - 60, 0xFFFFFF, hp_str);

	free(ammo_str);
	free(score_str);
	free(hp_str);
}
