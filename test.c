/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:23:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/02 15:48:10 by zjeyne-l         ###   ########.fr       */
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
	ft_draw_line(mlx, mlx->points[1].x, mlx->points[1].y, mlx->points[2].x, mlx->points[2].y, 0xFF00FF);

	ft_draw_line(mlx, mlx->player->x, mlx->player->y, mlx->player->x, mlx->player->y - 50, 0xFFFFFF);
	ft_draw_line(mlx, mlx->player->x, mlx->player->y, mlx->player->x, mlx->player->y, 0xFF00FF);
}

void	ft_rotate(t_mlx *mlx, int dir)
{
	ft_refresh_img(mlx);

	mlx->player->angle -= 0.1 * dir;

	int i = 0;
	int j = 0;
	while (i < 12)
	{
		double tx = mlx->points[j].x - mlx->player->x;
		double ty = mlx->points[j].y - mlx->player->y;

		double tz = tx * cos(0.05 * dir) + ty * sin(0.05 * dir);

		tx = tx * sin(0.05 * dir) - ty * cos(0.05 * dir);

		mlx->points[j].x = mlx->player->x - tx;
		mlx->points[j].y = mlx->player->y - tz;

		i++;
		j++;
		(j > 2) ? j = 0 : 1;
	}

	ft_draw_all(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	ft_move(t_mlx *mlx, int dir)
{
	ft_refresh_img(mlx);

	int i = 0;
	while (i < 3)
	{
		mlx->points[i].y += 25 * dir;
		i++;
	}

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
	(keycode == 0) ? ft_rotate(mlx, -1) : 1;
	(keycode == 2) ? ft_rotate(mlx, 1) : 1;
	(keycode == 13) ? ft_move(mlx, 1) : 1;
	(keycode == 1) ? ft_move(mlx, -1) : 1;
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