/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:55:55 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/21 21:56:08 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_ray_start(t_mlx *mlx)
{
	mlx->player->x = 12;
	mlx->player->y = 7.5;
	mlx->player->fov = 1.57;	//1.57			//1.02 -> 2.09
	mlx->player->pov = -1.6;
	mlx->depth = 32;
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
		double sample_x = 0;
		double eye_angle_x = sinf(mlx->iter_angle);//unit vector x
		double eye_angle_y = cosf(mlx->iter_angle);//unit vector y
		while (hit == 0 && dist_to_wall < mlx->depth)
		{
			dist_to_wall += 0.01;

			int t_x = mlx->player->x + (double)eye_angle_x * dist_to_wall;
			int t_y = mlx->player->y + (double)eye_angle_y * dist_to_wall;

			// out of bounds check
			if (t_x < 0 || t_x >= 15/*map width*/ || t_y < 0 || t_y >= 14/*map height*/)
			{
				hit = 1;
				dist_to_wall = mlx->depth;
				//printf("out\n");
			}
			else
			{
				if (ft_tiles_check(mlx->map, t_x, t_y))
				{
					//printf("asd\n");
					mlx->tile_index = -1;
					mlx->tile_index = ft_get_tile_index(mlx->map[t_y][t_x]);
					//printf("%c\n", mlx->map[t_y][t_x]);
					//printf("index %d\n", mlx->tile_index);
					hit = 1;
					//printf("asd\n");

					double block_mid_x = (double)t_x + 0.5;
					double block_mid_y = (double)t_y + 0.5;

					double point_x = mlx->player->x + eye_angle_x * dist_to_wall;
					double point_y = mlx->player->y + eye_angle_y * dist_to_wall;

					float angle = atan2f(point_y - block_mid_y, point_x - block_mid_x);

					if (angle >= -3.14159 * 0.25 && angle < 3.14159 * 0.25)
						sample_x = point_y - (double)t_y;
					if (angle >= 3.14159 * 0.25 && angle < 3.14159 * 0.75)
						sample_x = point_x - (double)t_x;
					if (angle < -3.14159 * 0.25 && angle >= -3.14159 * 0.75)
						sample_x = point_x - (double)t_x;
					if (angle >= 3.14159 * 0.75 || angle < -3.14159 * 0.75)
						sample_x = point_y - (double)t_y;
				}
			}
		}
		double ceiling = (double)(H / 2.0) - H / (double)dist_to_wall / mlx->player->fov;
		int floor = H - ceiling;

		int y = 0;
		while (y < H)
		{
			if (y <= ceiling)
				ft_image(mlx, x, y, 0x383838);
			else if (y > ceiling && y <= floor)
			{
				double sample_y = ((double)y - (double)ceiling) / ((double)floor - (double)ceiling);
				ft_image(mlx, x, y, ft_texture_sampling(mlx->textures[mlx->tile_index], sample_x, sample_y));
			}
			else
				ft_image(mlx, x, y, 0x6b6f6e);
			y++;
		}
		x++;
	}
	ft_draw_cross(mlx);
}
