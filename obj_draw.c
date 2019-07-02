/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:00:21 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/02 19:26:42 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_obj_dist_sort(t_mlx *mlx)
{
	int j;

	j = -1;
	while (++j < mlx->obj_count)
	{
		mlx->sprite_order[j] = j;
		mlx->sprite_dist[j] = (powf(mlx->objs[j]->x - mlx->player->x, 2)
							+ powf(mlx->objs[j]->y - mlx->player->y, 2));
	}
	ft_sort(mlx);
}

void	ft_obj_pos_calc(t_mlx *mlx, int i)
{
	mlx->vec_x = mlx->objs[mlx->sprite_order[i]]->x - mlx->player->x;
	mlx->vec_y = mlx->objs[mlx->sprite_order[i]]->y - mlx->player->y;
	mlx->dist_from_player = sqrtf(mlx->vec_x * mlx->vec_x
							+ mlx->vec_y * mlx->vec_y);
	mlx->eye_x = sinf(mlx->player->pov);
	mlx->eye_y = cosf(mlx->player->pov);
	mlx->obj_angle = atan2f(mlx->eye_y, mlx->eye_x)
							- atan2f(mlx->vec_y, mlx->vec_x);
	if (mlx->obj_angle < -3.14159)
		mlx->obj_angle += 2.0 * 3.14159;
	if (mlx->obj_angle > 3.14159)
		mlx->obj_angle -= 2.0 * 3.14159;
	mlx->in_fov = (fabs(mlx->obj_angle) <= mlx->player->fov / 1.0f) ? 1 : 0;
}

void	ft_obj_specs_calc(t_mlx *mlx, int i)
{
	mlx->obj_ceiling = (double)(H / 2.0) - (double)H
							/ (double)mlx->dist_from_player
							/ mlx->player->fov;
	mlx->obj_floor = (double)H - (double)mlx->obj_ceiling;
	mlx->obj_h = (double)mlx->obj_floor - (double)mlx->obj_ceiling;
	mlx->obj_aspect_ratio = (double)mlx->objs[mlx->sprite_order[i]]->img->w
							/ (double)mlx->objs[mlx->sprite_order[i]]->img->h;
	mlx->obj_w = (double)mlx->obj_h / (double)mlx->obj_aspect_ratio;
	mlx->obj_middle = (double)(0.5 * (mlx->obj_angle
							/ (mlx->player->fov / 2.0)) + 0.5) * (double)W;
}

void	ft_obj_sample_calc(t_mlx *mlx, int ox, int oy, int i)
{
	mlx->sample_ox = ox / mlx->obj_w;
	mlx->sample_oy = oy / mlx->obj_h;
	mlx->obj_color = ft_texture_sampling(
							mlx->objs[mlx->sprite_order[i]]->img,
							mlx->sample_ox, mlx->sample_oy);
	mlx->obj_col = (int)(mlx->obj_middle + ox - (mlx->obj_w / 2.0));
	if (mlx->obj_col >= 0 && mlx->obj_col < W)
		if (mlx->obj_color != IGNORE_COLOR
				&& mlx->depth_buff[mlx->obj_col] >= mlx->dist_from_player)
			ft_image(mlx, mlx->obj_col, mlx->obj_ceiling + oy, mlx->obj_color);
}

void	ft_objs_draw(t_mlx *mlx)
{
	int i;
	int ox;
	int oy;

	i = -1;
	ft_obj_dist_sort(mlx);
	while (++i < mlx->obj_count)
	{
		ft_obj_pos_calc(mlx, i);
		if (mlx->in_fov == 1 && mlx->dist_from_player < mlx->depth)
		{
			ft_obj_specs_calc(mlx, i);
			if (mlx->obj_h < H || mlx->obj_w < W)
			{
				ox = -1;
				while (++ox < mlx->obj_w)
				{
					oy = -1;
					while (++oy < mlx->obj_h)
						ft_obj_sample_calc(mlx, ox, oy, i);
				}
			}
		}
	}
}
