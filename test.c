/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:23:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/02/28 15:29:06 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_press(int keycode, t_mlx *mlx)
{
	(keycode == 53) ? exit(0) : 1;
	(keycode == 123) ? ft_view(mlx, -1) : 1;
	(keycode == 124) ? ft_view(mlx, 1) : 1;
	(keycode == 126) ? ft_player_move(mlx, -1) : 1;
	return (0);
}

int		main()
{
	t_mlx *mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->player = (t_player*)malloc(sizeof(t_player));
	mlx->points = (t_points*)malloc(sizeof(t_points) * 2);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "TEST");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int*)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	ft_draw_line(mlx, 460, 50 , 1460, 50, 0xFF00FF);
	mlx->points[0].x = 460;
	mlx->points[0].y = 50;
	mlx->points[1].x = 1460;
	mlx->points[1].y = 50;
	
	mlx->player->x = W / 2;
	mlx->player->y = H / 2;
	
	mlx->player->dir_xo = mlx->player->x;
	mlx->player->dir_yo = mlx->player->y - 5;
	mlx->player->dir_x = mlx->player->x;
	mlx->player->dir_y = mlx->player->y - 30;
	ft_draw_line(mlx, mlx->player->dir_xo, mlx->player->dir_yo, mlx->player->dir_x, mlx->player->dir_y, 0xFFFFFF);
	ft_image(mlx, mlx->player->x, mlx->player->y, 0xFF00FF);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

	mlx_hook(mlx->win, 2, 0, key_press, mlx);

	mlx_loop(mlx->mlx);
	return (0);
}