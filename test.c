/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:23:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/01 14:15:31 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_view_dir(t_mlx *mlx)
{
	mlx->player->dir_xo = mlx->player->x;
	mlx->player->dir_yo = mlx->player->y;
	mlx->player->dir_x = mlx->player->x + cos(mlx->player->pov) * 25;
	mlx->player->dir_y = mlx->player->y + sin(mlx->player->pov) * 25;

	ft_draw_line(mlx, mlx->player->dir_xo, mlx->player->dir_yo, mlx->player->dir_x, mlx->player->dir_y, 0xFFFFFF);
}

void	ft_start(t_mlx *mlx)
{
	ft_draw_line(mlx, 1460, 100 , 1460, 980, 0xFF00FF);
	mlx->points[0].x = 1460;
	mlx->points[0].y = 100;
	mlx->points[1].x = 1460;
	mlx->points[1].y = 980;
	
	mlx->player->x = W / 2;
	mlx->player->y = H / 2;
	mlx->player->pov = 0;
	
	ft_view_dir(mlx);

	ft_image(mlx, mlx->player->x, mlx->player->y, 0xFF00FF);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int		key_press(int keycode, t_mlx *mlx)
{
	(keycode == 53) ? exit(0) : 1;
	(keycode == 0) ? ft_view(mlx, -1) : 1;
	(keycode == 2) ? ft_view(mlx, 1) : 1;
	(keycode == 13) ? ft_player_move(mlx, -1) : 1;
	if (keycode == 15)
	{
		ft_reset_img(mlx);
		ft_start(mlx);
	}
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

	ft_start(mlx);

	mlx_hook(mlx->win, 2, 0, key_press, mlx);

	mlx_loop(mlx->mlx);
	return (0);
}