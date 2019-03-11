/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:55:55 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/11 21:43:21 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_ray_start(t_mlx *mlx)
{
	mlx->player->x = 8;
	mlx->player->y = 8;
	mlx->player->fov = 1.57;
	mlx->player->pov = 0;
	mlx->depth = 32;
	
	// mlx->proj_dist = W / 2 / tan(mlx->player->fov);
	// mlx->ray_angle = mlx->player->fov / W;
}

void	ft_ray_cast(t_mlx *mlx)
{
	int x;

	x = 0;
	while (x < W)
	{
		mlx->iter_angle = (mlx->player->pov - mlx->player->fov / 2.0) + ((double)x / (double)W) * mlx->player->fov;

		int hit = 0;
		int boundary = 0;
		double dist_to_wall = 0;
		double eye_x = sinf(mlx->iter_angle);//unit vector x
		double eye_y = cosf(mlx->iter_angle);//unit vector y
		while (hit == 0 && dist_to_wall < mlx->depth)
		{
			dist_to_wall += 0.01;

			int t_x = mlx->player->x + eye_x * dist_to_wall;
			int t_y = mlx->player->y + eye_y * dist_to_wall;

			// out of bounds check
			if (t_x < 0 || t_x >= 16/*map width*/ || t_y < 0 || t_y >= 16/*map height*/)
			{
				hit = 1;
				dist_to_wall = mlx->depth;
			}
			else
			{
				if (mlx->map[t_y][t_x] == '1')
				{
					hit = 1;

					// //vector

					// int tx = 0;
					// int ty;
					// while (tx < 2)
					// {
					// 	ty = 0;
					// 	while (ty < 2)
					// 	{
					// 		double vx = t_x + tx - mlx->player->x;
					// 		double vy = t_y + ty - mlx->player->y;
					// 		double d = sqrt(vx * vx + vy * vy);
					// 		double dot = (eye_x * vx / d) + (eye_y * vy / d);
							
					// 		ty++;
					// 	}
					// 	tx++;
					// }
				}
			}
		}
		int ceiling = (double)(H / 2.0) - H / (double)dist_to_wall;
		int floor = H - ceiling;
		int shade;

		if (dist_to_wall < mlx->depth / 4)
			shade = 0xc737373;
		else if (dist_to_wall < mlx->depth / 3)
			shade = 0x595959;
		else if (dist_to_wall < mlx->depth / 2)
			shade = 0x404040;
		else
			shade = 0x262626;

		int y = 0;
		while (y < H)
		{
			if (y <= ceiling)
				ft_image(mlx, x, y, 0x15171a);
			else if (y > ceiling && y <= floor)
				ft_image(mlx, x, y, shade);
			else
			{
				// double sh = 1.0 - (((double)y - H / 2.0) / ((double)H / 2.0));
				// if (sh < 0.25)
				// 	shade = 0x596669;
				// else if (sh < 0.5)
				// 	shade = 0x414a4d;
				// else if (sh < 0.75)
				// 	shade = 0x2a3133;
				// else if (sh < 0.9)
				// 	shade = 0x332318;
				// else
				// 	shade = 0x131617;
				ft_image(mlx, x, y, 0x15171a);
			}
			y++;
		}
		x++;
	}
}
