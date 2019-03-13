/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:55:55 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/13 23:01:17 by zjeyne-l         ###   ########.fr       */
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
		double sample_x = 0;
		double eye_angle_x = sinf(mlx->iter_angle);//unit vector x
		double eye_angle_y = cosf(mlx->iter_angle);//unit vector y
		while (hit == 0 && dist_to_wall < mlx->depth)
		{
			dist_to_wall += 0.01;

			int t_x = mlx->player->x + (double)eye_angle_x * dist_to_wall;
			int t_y = mlx->player->y + (double)eye_angle_y * dist_to_wall;

			// out of bounds check
			if (t_x < 0 || t_x >= 16/*map width*/ || t_y < 0 || t_y >= 24/*map height*/)
			{
				hit = 1;
				dist_to_wall = mlx->depth;
			}
			else
			{
				if (mlx->map[t_y][t_x] == WALL)
				{
					hit = 1;

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
		int ceiling = (double)(H / 2.0) - H / (double)dist_to_wall;
		int floor = H - ceiling;
		int shade;
		
		if (dist_to_wall < mlx->depth / 6)
			shade = 0xb3b3b3;
		else if (dist_to_wall < mlx->depth / 5)
			shade = 0x808080;
		else if (dist_to_wall < mlx->depth / 4)
			shade = 0x666666;
		else if (dist_to_wall < mlx->depth / 3)
			shade = 0x4d4d4d;
		else if (dist_to_wall < mlx->depth / 2)
			shade = 0x333333;
		else
			shade = 0x242424;

		int y = 0;
		while (y < H)
		{
			if (y <= ceiling)
				ft_image(mlx, x, y, 0x15171a);
			else if (y > ceiling && y <= floor)
			{
				double sample_y = ((double)y - (double)ceiling) / ((double)floor - (double)ceiling);
				ft_image(mlx, x, y, mlx->textures[0][ft_texture_sampling(mlx, sample_x, sample_y)]);
				//ft_image(mlx, x, y, shade);
			}
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
	ft_draw_cross(mlx);
}
