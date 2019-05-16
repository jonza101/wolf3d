/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:55:55 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/16 14:44:29 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_part(t_mlx *mlx, int begin, int end)
{
	int low = begin;
	int high = end;
	int pivot = mlx->sprite_order[(begin + end) / 2];
	printf("%d\n", mlx->sprite_order[(begin + end) / 2]);
	while (low <= high)
	{
		while (mlx->sprite_order[low] < pivot)
			low++;
		while (mlx->sprite_order[high] > pivot)
			high--;
		if (low >= high)
			break;

		int tmp = mlx->sprite_order[low++];
		mlx->sprite_order[low++] = mlx->sprite_order[high--];
		mlx->sprite_order[high--] = tmp;
		
		double temp = mlx->sprite_dist[low++];
		mlx->sprite_dist[low++] = mlx->sprite_dist[high--];
		mlx->sprite_dist[high--] = temp;
	}
	return (high);
}

void	ft_qsort(t_mlx *mlx, int begin, int end)
{
	int high = ft_part(mlx, begin, end);
	ft_qsort(mlx, begin, high);
	ft_qsort(mlx, high + 1, end);
}

void	ft_sort(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while (i < mlx->obj_count - 1)
	{
		j = i + 1;
		while (j < mlx->obj_count)
		{
			if (mlx->sprite_dist[i] < mlx->sprite_dist[j])
			{
				int tmp = mlx->sprite_order[i];
				mlx->sprite_order[i] = mlx->sprite_order[j];
				mlx->sprite_order[j] = tmp;

				double temp = mlx->sprite_dist[i];
				mlx->sprite_dist[i] = mlx->sprite_dist[j];
				mlx->sprite_dist[j] = temp;
			}
			j++;
		}
		i++;
	}
}

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
								ft_image(mlx, obj_col, obj_ceiling + oy, color);
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
	int j = 0;
	while (j < mlx->obj_count)
    {
		mlx->sprite_order[j] = j;
		mlx->sprite_dist[j] = (powf(mlx->objs[j]->x - mlx->player->x, 2) + powf(mlx->objs[j]->y - mlx->player->y, 2));
		j++;
    }
	ft_sort(mlx);

	int i = 0;

	while (i < mlx->obj_count)
	{
		double vector_x = mlx->objs[mlx->sprite_order[i]]->x - mlx->player->x;
		double vector_y = mlx->objs[mlx->sprite_order[i]]->y - mlx->player->y;

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
			double obj_aspect_ratio =  (double)mlx->objs[mlx->sprite_order[i]]->img->w / (double)mlx->objs[mlx->sprite_order[i]]->img->h;
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

						int color = ft_texture_sampling(mlx->objs[mlx->sprite_order[i]]->img, sample_ox, sample_oy);

						int obj_col = (int)(obj_middle + ox - (obj_w / 2.0));
						if (obj_col >= 0 && obj_col < W)
							if (color != 0x980088 && mlx->depth_buff[obj_col] >= dist_from_player)
									ft_image(mlx, obj_col, obj_ceiling + oy, color);
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
		double eye_angle_x = sinf(mlx->iter_angle);	//unit vector x
		double eye_angle_y = cosf(mlx->iter_angle);	//unit vector y
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
		// dist_to_wall *= ((eye_angle_x * sinf(mlx->player->pov)) + (eye_angle_y * cosf(mlx->player->pov))) / (mlx->player->fov / 2);
		// double ceiling = (double)(H / 2.0) * (1.0 - 1.0 / dist_to_wall / 0.95);

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
