/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:23:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/03 18:00:43 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#include <stdio.h>

double	ft_fn_cross(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - y1 * x2);
}

void	ft_intersects(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double *x, double *y)
{
	*x = ft_fn_cross(x1, y1, x2, y2);
	*y = ft_fn_cross(x3, y3, x4, y4);
	double det = ft_fn_cross(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	*x = ft_fn_cross(*x, x1 - x2, *y, x3 - x4) / det;
	*y = ft_fn_cross(*x, y1 - y2, *y, y3 - y4) / det;
}

void	ft_refresh_img(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx_clear_window(mlx->mlx, mlx->win);
}

void	ft_draw_all(t_mlx *mlx)
{
	ft_draw_line(mlx, mlx->points[0].x, mlx->points[0].y, mlx->points[1].x, mlx->points[1].y, 0xFF00FF);
	ft_draw_line(mlx, mlx->points[1].x, mlx->points[1].y, mlx->points[2].x, mlx->points[2].y, 0xFF00FF);

	ft_draw_line(mlx, mlx->player->x, mlx->player->y - 5, mlx->player->x, mlx->player->y - 50, 0xFFFFFF);
	ft_draw_line(mlx, mlx->player->x, mlx->player->y, mlx->player->x, mlx->player->y, 0xFF00FF);
}

void	ft_rotate(t_mlx *mlx, int dir)
{
	ft_refresh_img(mlx);

	mlx->player->angle += 0.005 * dir;
	printf("angle %f\n\n", mlx->player->angle);

	int i = 0;
	int j = 0;
	//printf("x %f			y %f\n", mlx->points[0].x, mlx->points[0].y);
	while (i < 4) // 4? //
	{		
		double tx0 = mlx->points[0].x - mlx->player->x;
		double ty0 = mlx->points[0].y - mlx->player->y;

		double tx1 = mlx->points[1].x - mlx->player->x;
		double ty1 = mlx->points[1].y - mlx->player->y;

		double tx2 = mlx->points[2].x - mlx->player->x;
		double ty2 = mlx->points[2].y - mlx->player->y;

		double tz0 = tx0 * cos(0.005 * dir) + ty0 * sin(0.005 * dir);
		double tz1 = tx1 * cos(0.005 * dir) + ty1 * sin(0.005 * dir);
		double tz2 = tx2 * cos(0.005 * dir) + ty2 * sin(0.005 * dir);

		tx0 = tx0 * sin(0.005 * dir) - ty0 * cos(0.005 * dir);
		tx1 = tx1 * sin(0.005 * dir) - ty1 * cos(0.005 * dir);
		tx2 = tx2 * sin(0.005 * dir) - ty2 * cos(0.005 * dir); 


		mlx->points[0].x = mlx->player->x - tx0;
		mlx->points[0].y = mlx->player->y - tz0;									// HERE IS THE PROBLEM (DO NOT CHANGE THE POINT POS)!!!

		mlx->points[1].x = mlx->player->x - tx1;
		mlx->points[1].y = mlx->player->y - tz1;

		mlx->points[2].x = mlx->player->x - tx2;
		mlx->points[2].y = mlx->player->y - tz2;


		if (i == 3) // == 3?
		{
			if (tz0 > 0 || tz1 > 0 || tz2 > 0)
			{
				double ix0, iz0;
				double ix1, iz1;
				double ix2, iz2;
				ft_intersects(tx0, tz0, tx1, tz1, -0.0001, 0.0001, -20, 5, &ix0, &iz0);
				ft_intersects(tx0, tz0, tx1, tz1, 0.0001, 0.0001, 20, 5, &ix1, &iz1);

				if (tz0 <= 0)
				{
					
					if (iz0 > 0)
					{
						//printf("less0->more\n");
						tx0 = ix0;
						tz0 = iz0;
					}
					else
					{
						//printf("less0->less\n");
						tx0 = ix1;
						tz0 = iz1;
					}
				}
				if (tz1 <= 0)
				{
					
					if (iz0 > 0)
					{
						//printf("less1->more\n");
						tx1 = ix0;
						tz1 = iz0;
					}
					else
					{
						//printf("less1->less\n");
						tx1 = ix1;
						tz1 = iz1;
					}
				}

				ft_intersects(tx1, tz1, tx2, tz2, -0.0001, 0.0001, -20, 5, &ix1, &iz1);
				ft_intersects(tx1, tz1, tx2, tz2, 0.0001, 0.0001, 20, 5, &ix2, &iz2);

				if (tz1 <= 0)
				{
					
					if (iz1 > 0)
					{
						//printf("less1->more\n");
						tx1 = ix1;
						tz1 = iz1;
					}
					else
					{
						//printf("less1->less\n");
						tx1 = ix2;
						tz1 = iz2;
					}
				}

				if (tz2 <= 0)
				{
					
					if (iz1 > 0)
					{
						//printf("less0->more\n");
						tx2 = ix1;
						tz2 = iz1;
					}
					else
					{
						//printf("less0->less\n");
						tx2 = ix2;
						tz2 = iz2;
					}
				}

				double x0 = -tx0 * 16 / tz0;
				double y0a = -mlx->player->x / tz0;
				double y0b = mlx->player->y / tz0;

				double x1 = -tx1 * 16 / tz1;
				double y1a = -mlx->player->x / tz1;
				double y1b = mlx->player->y / tz1;

				double x2 = -tx2 * 16 / tz2;
				double y2a = -mlx->player->x / tz2;
				double y2b = mlx->player->x / tz2;

				ft_draw_line(mlx, mlx->player->x + x0, mlx->player->y + y0a, mlx->player->x + x1, mlx->player->y + y1a, 0xFFFFFF);
				ft_draw_line(mlx, mlx->player->x + x0, mlx->player->y + y0b, mlx->player->x + x1, mlx->player->y + y1b, 0xFFFFFF);
				ft_draw_line(mlx, mlx->player->x + x0, mlx->player->y + y0a, mlx->player->x + x0, mlx->player->y + y0b, 0xFFFFFF);
				ft_draw_line(mlx, mlx->player->x + x1, mlx->player->y + y1a, mlx->player->x + x1, mlx->player->y + y1b, 0xFFFFFF);

				ft_draw_line(mlx, mlx->player->x + x1, mlx->player->y + y1a, mlx->player->x + x2, mlx->player->y + y2a, 0xFFFFFF);
				ft_draw_line(mlx, mlx->player->x + x1, mlx->player->y + y1b, mlx->player->x + x2, mlx->player->y + y2b, 0xFFFFFF);
				ft_draw_line(mlx, mlx->player->x + x1, mlx->player->y + y1a, mlx->player->x + x1, mlx->player->y + y1b, 0xFFFFFF);
				ft_draw_line(mlx, mlx->player->x + x2, mlx->player->y + y2a, mlx->player->x + x2, mlx->player->y + y2b, 0xFFFFFF);	
			}
		}

		i++;
		// j++;
		// (j > 2) ? j = 0 : 1;
	}
	//printf("x %f			y %f\n", mlx->points[0].x, mlx->points[0].y);

	ft_draw_all(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	ft_move_x(t_mlx *mlx, int dir)
{
	ft_refresh_img(mlx);

	int i = 0;
	while (i < 3)
	{
		mlx->points[i].x += 10 * dir;
		i++;
	}

	ft_rotate(mlx, 0);

	ft_draw_all(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	ft_move_y(t_mlx *mlx, int dir)
{
	ft_refresh_img(mlx);

	int i = 0;
	while (i < 3)
	{
		mlx->points[i].y += 10 * dir;
		i++;
	}

	ft_rotate(mlx, 0);

	ft_draw_all(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	ft_start(t_mlx *mlx)
{
	mlx->points[0].x = 600;
	mlx->points[0].y = 300;
	mlx->points[1].x = 1200;
	mlx->points[1].y = 300;
	mlx->points[2].x = 1200;
	mlx->points[2].y = 900;

	mlx->player->x = W / 2;
	mlx->player->y = H / 2;
	mlx->player->angle = 0;

	ft_rotate(mlx, 0);

	ft_draw_all(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	if (button == 3)
		printf("x %d			y %d\n\n", x, y);
	return (0);
}

int		key_press(int keycode, t_mlx *mlx)
{
	(keycode == 53) ? exit(0) : 1;
	(keycode == 123) ? ft_rotate(mlx, -1) : 1;
	(keycode == 124) ? ft_rotate(mlx, 1) : 1;
	(keycode == 13) ? ft_move_y(mlx, 1) : 1;
	(keycode == 1) ? ft_move_y(mlx, -1) : 1;
	(keycode == 0) ? ft_move_x(mlx, 1) : 1;
	(keycode == 2) ? ft_move_x(mlx, -1) : 1;
	if (keycode == 15)
	{
		ft_refresh_img(mlx);
		ft_start(mlx);
	}
	return (0);
}

int		main(void)
{
	t_mlx *mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->player = (t_player*)malloc(sizeof(t_player));
	mlx->points = (t_points*)malloc(sizeof(t_points) * 3);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "TEST");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int*)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	ft_start(mlx);

	mlx_hook(mlx->win, 2, 0, key_press, mlx);
	mlx_hook(mlx->win, 4, 0, mouse_press, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}