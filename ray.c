/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:55:55 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/22 17:56:23 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_ray_start(t_mlx *mlx)
{
	mlx->player->x = 12;
	mlx->player->y = 29.5;
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
		double dist_to_wall = 0;
		double sample_x = 0;
		double eye_angle_x = sinf(mlx->iter_angle);//unit vector x
		double eye_angle_y = cosf(mlx->iter_angle);//unit vector y
		while (hit == 0 && dist_to_wall < mlx->depth)
		{
			dist_to_wall += 0.01;

			int p_x = mlx->player->x + (double)eye_angle_x * dist_to_wall;
			int p_y = mlx->player->y + (double)eye_angle_y * dist_to_wall;

			// out of bounds check
			if (p_x < 0 || p_x >= 17/*map width*/ || p_y < 0 || p_y >= 36/*map height*/)
			{
				hit = 1;
				dist_to_wall = mlx->depth;
				//printf("out\n");
			}
			else
			{
				if (ft_tiles_check(mlx->map, p_x, p_y))
				{
					//printf("asd\n");
					mlx->tile_index = -1;
					mlx->tile_index = ft_get_tile_index(mlx->map[p_y][p_x]);
					//printf("%c\n", mlx->map[p_y][p_x]);
					//printf("index %d\n", mlx->tile_index);
					hit = 1;
					//printf("asd\n");

					double block_mid_x = (double)p_x + 0.5;
					double block_mid_y = (double)p_y + 0.5;

					double poinp_x = mlx->player->x + eye_angle_x * dist_to_wall;
					double poinp_y = mlx->player->y + eye_angle_y * dist_to_wall;

					float angle = atan2f(poinp_y - block_mid_y, poinp_x - block_mid_x);

					if (angle >= -3.14159 * 0.25 && angle < 3.14159 * 0.25)
						sample_x = poinp_y - (double)p_y;
					if (angle >= 3.14159 * 0.25 && angle < 3.14159 * 0.75)
						sample_x = poinp_x - (double)p_x;
					if (angle < -3.14159 * 0.25 && angle >= -3.14159 * 0.75)
						sample_x = poinp_x - (double)p_x;
					if (angle >= 3.14159 * 0.75 || angle < -3.14159 * 0.75)
						sample_x = poinp_y - (double)p_y;
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
				if (dist_to_wall < mlx->depth)
				{
					double sample_y = ((double)y - (double)ceiling) / ((double)floor - (double)ceiling);
					ft_image(mlx, x, y, ft_texture_sampling(mlx->textures[mlx->tile_index], sample_x, sample_y));
				}
				else
					ft_image(mlx, x, y, 0x383838);
			}
			else
				ft_image(mlx, x, y, 0x6b6f6e);
			y++;
		}
		x++;
	}
	ft_draw_cross(mlx);
}
