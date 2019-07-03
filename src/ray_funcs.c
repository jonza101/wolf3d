/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 18:11:02 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/03 13:00:28 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_hit_calc(t_mlx *mlx)
{
	mlx->dist_to_wall += 0.01;
	mlx->p_x = mlx->player->x + (double)mlx->eye_angle_x * mlx->dist_to_wall;
	mlx->p_y = mlx->player->y + (double)mlx->eye_angle_y * mlx->dist_to_wall;
	if (mlx->p_x < 0 || mlx->p_x >= mlx->col
			|| mlx->p_y < 0 || mlx->p_y >= mlx->row)
	{
		mlx->hit = 1;
		mlx->dist_to_wall = mlx->depth;
	}
	else
	{
		if (ft_tiles_check(mlx->map, mlx->p_x, mlx->p_y))
			ft_texturing_calc(mlx, mlx->p_x, mlx->p_y);
	}
}

void	ft_ray_iter_init(t_mlx *mlx, int x)
{
	mlx->iter_angle = (mlx->player->pov - mlx->player->fov / 2.0)
					+ ((double)x / (double)W) * mlx->player->fov;
	mlx->hit = 0;
	mlx->dist_to_wall = 0;
	mlx->sample_x = 0;
	mlx->eye_angle_x = sinf(mlx->iter_angle);
	mlx->eye_angle_y = cosf(mlx->iter_angle);
}

void	ft_texturing_calc(t_mlx *mlx, int p_x, int p_y)
{
	mlx->tile_index = ft_get_tile_index(mlx->map[p_y][p_x]);
	mlx->hit = 1;
	mlx->block_mid_x = (double)p_x + 0.5;
	mlx->block_mid_y = (double)p_y + 0.5;
	mlx->point_x = mlx->player->x + mlx->eye_angle_x * mlx->dist_to_wall;
	mlx->point_y = mlx->player->y + mlx->eye_angle_y * mlx->dist_to_wall;
	mlx->txt_angle = atan2f(mlx->point_y - mlx->block_mid_y,
							mlx->point_x - mlx->block_mid_x);
	if (mlx->txt_angle >= -3.14159 * 0.25 && mlx->txt_angle < 3.14159 * 0.25)
		mlx->sample_x = mlx->point_y - (double)p_y;
	if (mlx->txt_angle >= 3.14159 * 0.25 && mlx->txt_angle < 3.14159 * 0.75)
		mlx->sample_x = mlx->point_x - (double)p_x;
	if (mlx->txt_angle < -3.14159 * 0.25 && mlx->txt_angle >= -3.14159 * 0.75)
		mlx->sample_x = mlx->point_x - (double)p_x;
	if (mlx->txt_angle >= 3.14159 * 0.75 || mlx->txt_angle < -3.14159 * 0.75)
		mlx->sample_x = mlx->point_y - (double)p_y;
}

void	ft_col_fill(t_mlx *mlx, int x)
{
	int y;

	y = 0;
	while (y < H)
	{
		if (y <= mlx->ceiling)
			ft_image(mlx, x, y, CEILING);
		else if (y > mlx->ceiling && y <= mlx->floor)
		{
			if (mlx->dist_to_wall < mlx->depth)
			{
				mlx->sample_y = ((double)y - (double)mlx->ceiling)
								/ ((double)mlx->floor - (double)mlx->ceiling);
				ft_image(mlx, x, y, ft_texture_sampling(
								mlx->textures[mlx->tile_index],
								mlx->sample_x, mlx->sample_y));
			}
			else
				ft_image(mlx, x, y, CEILING);
		}
		else
			ft_image(mlx, x, y, FLOOR);
		y++;
	}
}
