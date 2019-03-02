/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:23:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/02 19:11:04 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_refresh_img(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx_clear_window(mlx->mlx, mlx->win);
}

void	ft_draw_all(t_mlx *mlx)
{
	ft_draw_line(mlx, mlx->points[0].x, mlx->points[0].y, mlx->points[1].x, mlx->points[1].y, 0xFF00FF);
	//ft_draw_line(mlx, mlx->points[1].x, mlx->points[1].y, mlx->points[2].x, mlx->points[2].y, 0xFF00FF);

	ft_draw_line(mlx, mlx->player->x, mlx->player->y - 5, mlx->player->x, mlx->player->y - 50, 0xFFFFFF);
	ft_draw_line(mlx, mlx->player->x, mlx->player->y, mlx->player->x, mlx->player->y, 0xFF00FF);
}

void	ft_rotate(t_mlx *mlx, int dir)
{
	ft_refresh_img(mlx);

	mlx->player->angle -= 0.01 * dir;
	//printf("angle %f\n\n", mlx->player->angle);

	int i = 0;
	int j = 0;
	//printf("x %f			y %f\n", mlx->points[0].x, mlx->points[0].y);
	while (i < 4)
	{		
		double tx0 = mlx->points[0].x - mlx->player->x;
		double ty0 = mlx->points[0].y - mlx->player->y;

		double tx1 = mlx->points[1].x - mlx->player->x;
		double ty1 = mlx->points[1].y - mlx->player->y;

		double tx2 = mlx->points[2].x - mlx->player->x;
		double ty2 = mlx->points[2].y - mlx->player->y;

		double tz0 = tx0 * cos(0.01 * dir) + ty0 * sin(0.01 * dir);
		double tz1 = tx1 * cos(0.01 * dir) + ty1 * sin(0.01 * dir);
		double tz2 = tx2 * cos(0.01 * dir) + ty2 * sin(0.01 * dir);

		tx0 = tx0 * sin(0.01 * dir) - ty0 * cos(0.01 * dir);
		tx1 = tx1 * sin(0.01 * dir) - ty1 * cos(0.01 * dir);
		tx2 = tx2 * sin(0.01 * dir) - ty2 * cos(0.01 * dir);


		mlx->points[0].x = mlx->player->x - tx0;
		mlx->points[0].y = mlx->player->y - tz0;

		mlx->points[1].x = mlx->player->x - tx1;
		mlx->points[1].y = mlx->player->y - tz1;

		mlx->points[2].x = mlx->player->x - tx2;
		mlx->points[2].y = mlx->player->y - tz2;


		if (i == 3)
		{
			double x0 = -tx0 * 16 / tz0;
			double y0a = -mlx->player->x / tz0;
			double y0b = mlx->player->y / tz0;

			double x1 = -tx1 * 16 / tz1;
			double y1a = -mlx->player->x / tz1;
			double y1b = mlx->player->y / tz1;

			double x2 = -tx2 * 16 / tz2;
			double y2a = -mlx->player->x / tz2;
			double y2b = mlx->player->x / tz2;

			ft_draw_line(mlx, mlx->player->x + x0, mlx->player->y + y0a, mlx->player->x + x1, mlx->player->y + y1a, 0xFF00FF);
			ft_draw_line(mlx, mlx->player->x + x0, mlx->player->y + y0b, mlx->player->x + x1, mlx->player->y + y1b, 0xFF00FF);
			ft_draw_line(mlx, mlx->player->x + x0, mlx->player->y + y0a, mlx->player->x + x0, mlx->player->y + y0b, 0xFF00FF);
			ft_draw_line(mlx, mlx->player->x + x1, mlx->player->y + y1a, mlx->player->x + x1, mlx->player->y + y1b, 0xFF00FF);

			// ft_draw_line(mlx, mlx->player->x + x1, mlx->player->y + y1a, mlx->player->x + x2, mlx->player->y + y2a, 0xFF00FF);
			// ft_draw_line(mlx, mlx->player->x + x1, mlx->player->y + y1b, mlx->player->x + x2, mlx->player->y + y2b, 0xFF00FF);
			// ft_draw_line(mlx, mlx->player->x + x1, mlx->player->y + y1a, mlx->player->x + x1, mlx->player->y + y1b, 0xFF00FF);
			// ft_draw_line(mlx, mlx->player->x + x2, mlx->player->y + y2a, mlx->player->x + x2, mlx->player->y + y2b, 0xFF00FF);
		}

		i++;
		j++;
		(j > 2) ? j = 0 : 1;
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
		mlx->points[i].x += 25 * dir;
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
		mlx->points[i].y += 25 * dir;
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

	ft_rotate(mlx, 1);

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