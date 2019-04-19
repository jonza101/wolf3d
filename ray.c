/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:55:55 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/04/19 18:19:56 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_ray_start(t_mlx *mlx)
{
	mlx->player->x = mlx->player->start_x;
	mlx->player->y = mlx->player->start_y;
	mlx->player->fov = 1.57;	//1.57			//1.02 -> 2.09
	mlx->player->pov = -1.57;
	mlx->depth = 32;

	mlx->player->ammo = 0;
	mlx->player->score = 0;
	mlx->player->hp = 100;
}

void	ft_cobjs_draw(t_mlx *mlx)
{
	int i = 0;
	t_cobj * temp;
	
	temp = mlx->cobjs;
	while (mlx->cobjs)
	{
		double vector_x = mlx->cobjs->x - mlx->player->x;
		double vector_y = mlx->cobjs->y - mlx->player->y;

		double dist_from_player = sqrtf(vector_x * vector_x + vector_y * vector_y);

		double eye_x = sinf(mlx->player->pov);
		double eye_y = cosf(mlx->player->pov);
		double obj_angle = atan2f(eye_y, eye_x) - atan2f(vector_y, vector_x);
		if (obj_angle < -3.14159)
			obj_angle += 2.0 * 3.14159;
		if (obj_angle > 3.14159)
			obj_angle -= 2.0 * 3.14159;

		int in_fov = (fabs(obj_angle) <= mlx->player->fov / 2.0) ? 1 : 0;

		if (in_fov == 1 && dist_from_player < mlx->depth)
		{
			double obj_ceiling = (double)(H / 2.0) - (double)H / (double)dist_from_player / mlx->player->fov;
			double obj_floor = (double)H - (double)obj_ceiling;
			double obj_h = (double)obj_floor - (double)obj_ceiling;
			double obj_aspect_ratio = (double)mlx->cobjs->img->h / (double)mlx->cobjs->img->w;
			double obj_w = (double)obj_h / (double)obj_aspect_ratio;

			double obj_middle = (double)(0.5 * (obj_angle / (mlx->player->fov / 2.0)) + 0.5) * (double)W;

			if (obj_h < H || obj_w < W)
			{
				int ox = 0;
				while (ox < obj_w)
				{
					int oy = 0;
					while (oy < obj_h)
					{
						double sample_ox = ox / obj_w;
						double sample_oy = oy / obj_h;

						int color = ft_texture_sampling(mlx->cobjs->img, sample_ox, sample_oy);

						int obj_col = (int)(obj_middle + ox - (obj_w / 2.0));
						if (obj_col >= 0 && obj_col < W)
							if (color != 0x980088 && mlx->depth_buff[obj_col] >= dist_from_player)
							{
								ft_image(mlx, obj_col, obj_ceiling + oy, color);
								//mlx->depth_buff[obj_col] = dist_from_player;
								//(mlx->cobjs->is_lamp == 0) ? mlx->depth_buff[obj_col] = dist_from_player : 1;
							}
						oy++;
					}
					ox++;
				}
			}
		}
		mlx->cobjs = mlx->cobjs->next_cobj;
	}
	mlx->cobjs = temp;
}

void	ft_objs_draw(t_mlx *mlx)
{
	int i = 0;
	while (i < mlx->obj_count)
	{
		double vector_x = mlx->objs[i]->x - mlx->player->x;
		double vector_y = mlx->objs[i]->y - mlx->player->y;

		double dist_from_player = sqrtf(vector_x * vector_x + vector_y * vector_y);

		double eye_x = sinf(mlx->player->pov);
		double eye_y = cosf(mlx->player->pov);
		double obj_angle = atan2f(eye_y, eye_x) - atan2f(vector_y, vector_x);
		if (obj_angle < -3.14159)
			obj_angle += 2.0 * 3.14159;
		if (obj_angle > 3.14159)
			obj_angle -= 2.0 * 3.14159;

		int in_fov = (fabs(obj_angle) <= mlx->player->fov / 2.0) ? 1 : 0;

		if (in_fov == 1 && dist_from_player < mlx->depth)
		{
			double obj_ceiling = (double)(H / 2.0) - (double)H / (double)dist_from_player / mlx->player->fov;
			double obj_floor = (double)H - (double)obj_ceiling;
			double obj_h = (double)obj_floor - (double)obj_ceiling;
			double obj_aspect_ratio =  (double)mlx->objs[i]->img->w / (double)mlx->objs[i]->img->h;
			double obj_w = (double)obj_h / (double)obj_aspect_ratio;

			double obj_middle = (double)(0.5 * (obj_angle / (mlx->player->fov / 2.0)) + 0.5) * (double)W;

			if (obj_h < H || obj_w < W)
			{
				// if (obj_h > H)
				// {
				// 	printf("h %f		w %f\n\n", obj_h, obj_w);
				// 	obj_h = H;
				// 	obj_w = (double)obj_h / (double)obj_aspect_ratio;
				// }
				int ox = 0;
				while (ox < obj_w)
				{
					int oy = 0;
					while (oy < obj_h)
					{
						double sample_ox = ox / obj_w;
						double sample_oy = oy / obj_h;

						int color = ft_texture_sampling(mlx->objs[i]->img, sample_ox, sample_oy);

						int obj_col = (int)(obj_middle + ox - (obj_w / 2.0));
						if (obj_col >= 0 && obj_col < W)
							if (color != 0x980088 && mlx->depth_buff[obj_col] >= dist_from_player)
								{
									ft_image(mlx, obj_col, obj_ceiling + oy, color);
									//mlx->depth_buff[obj_col] = dist_from_player;
									(mlx->objs[i]->is_lamp == 0) ? mlx->depth_buff[obj_col] = dist_from_player : 1;
								}
						oy++;
					}
					ox++;
				}
			}
		}
		i++;
	}
}

void	ft_ray_cast(t_mlx *mlx)
{
	int x;
	int w;

	x = (W / THREAD) * (mlx->mlx_index % THREAD);
	w = (W / THREAD) * (mlx->mlx_index % THREAD) + (W / THREAD);
	while (x < w)
	{
		mlx->iter_angle = (mlx->player->pov - mlx->player->fov / 2.0) + ((double)x / (double)W) * mlx->player->fov;
		// mlx->iter_angle = mlx->player->pov + atanf((2.0 * (double)x / (double)W - 1.0) *  tanf(mlx->player->fov / 2.0));

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
			if (p_x < 0 || p_x >= mlx->col/*MAP WIDTH*/ || p_y < 0 || p_y >= mlx->row/*MAP HEIGHT*/)
			{
				hit = 1;
				dist_to_wall = mlx->depth;
			}
			else
			{
				if (ft_tiles_check(mlx->map, p_x, p_y))
				{
					mlx->tile_index = ft_get_tile_index(mlx->map[p_y][p_x]);
					hit = 1;

					double block_mid_x = (double)p_x + 0.5;
					double block_mid_y = (double)p_y + 0.5;

					double point_x = mlx->player->x + eye_angle_x * dist_to_wall;
					double point_y = mlx->player->y + eye_angle_y * dist_to_wall;

					float angle = atan2f(point_y - block_mid_y, point_x - block_mid_x);

					if (angle >= -3.14159 * 0.25 && angle < 3.14159 * 0.25)
						sample_x = point_y - (double)p_y;
					if (angle >= 3.14159 * 0.25 && angle < 3.14159 * 0.75)
						sample_x = point_x - (double)p_x;
					if (angle < -3.14159 * 0.25 && angle >= -3.14159 * 0.75)
						sample_x = point_x - (double)p_x;
					if (angle >= 3.14159 * 0.75 || angle < -3.14159 * 0.75)
						sample_x = point_y - (double)p_y;
				}
			}
		}
		//double dst = ((eye_angle_x * sinf(mlx->player->pov)) + (eye_angle_y * cosf(mlx->player->pov))) * dist_to_wall;// * mlx->player->fov;
		// double ceiling = (double)(H / 2.0) * (1.0 - 1.0 / dst / 1);

		// double screen_halflen = dist_to_wall * tanf(mlx->player->fov / 2);
		// double seg_len = (double)screen_halflen / ((double)W / 2.0);
		// dist_to_wall *= cosf(atan(((seg_len * x - screen_halflen) / dist_to_wall)));

		double ceiling = (double)(H / 2.0) - H / (double)dist_to_wall / mlx->player->fov;
		int floor = H - ceiling;

		mlx->depth_buff[x] = dist_to_wall;

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
}
