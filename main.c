/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:40:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/04/23 21:48:55 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#include <stdio.h>

void ft_reset_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	mlx_clear_window(mlx->mlx, mlx->win);
}

int		key_press(int keycode, t_mlx *mlx)
{
	//printf("%d\n", keycode);
	(keycode == 65307) ? exit(0) : 1;

	if (keycode == 61 && mlx->player->fov < 2.09)
	{
		ft_reset_image(mlx);
		mlx->player->fov += 0.02;
		printf("fov %f\n", mlx->player->fov);
		ft_thread(mlx);
	}

	if (keycode == 45 && mlx->player->fov > 1.02)
	{
		ft_reset_image(mlx);
		mlx->player->fov -= 0.02;
		printf("fov %f\n", mlx->player->fov);
		ft_thread(mlx);
	}

	if (keycode == 65361)
	{
		ft_reset_image(mlx);
		mlx->player->pov -= 0.065;
		ft_thread(mlx);
	}

	if (keycode == 65363)
	{
		ft_reset_image(mlx);
		mlx->player->pov += 0.065;
		ft_thread(mlx);
	}

	if (keycode == 1731)	//FORWARD
	{
		ft_reset_image(mlx);

		if ((ft_walls_check(mlx->map, (int)(mlx->player->x + sinf(mlx->player->pov) * 0.8), (int)mlx->player->y)))
			mlx->player->x += sinf(mlx->player->pov) * 0.35;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y + cosf(mlx->player->pov) * 0.8)))
			mlx->player->y += cosf(mlx->player->pov) * 0.35;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
		ft_thread(mlx);
	}

	if (keycode == 1753)	//BACK
	{
		ft_reset_image(mlx);

		if ((ft_walls_check(mlx->map, (int)(mlx->player->x - sinf(mlx->player->pov) * 0.8), (int)mlx->player->y)))
			mlx->player->x -= sinf(mlx->player->pov) * 0.35;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y - cosf(mlx->player->pov) * 0.8)))
			mlx->player->y -= cosf(mlx->player->pov) * 0.35;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
		ft_thread(mlx);
	}

	if (keycode == 1751)	//RIGHT
	{
		ft_reset_image(mlx);

		if (ft_walls_check(mlx->map, (int)(mlx->player->x + cosf(mlx->player->pov) * 0.5), (int)mlx->player->y))
			mlx->player->x += cosf(mlx->player->pov) * 0.25;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y - sinf(mlx->player->pov) * 0.5)))
			mlx->player->y -= sinf(mlx->player->pov) * 0.25;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
		ft_thread(mlx);
	}

	if (keycode == 1734)	//LEFT
	{
		ft_reset_image(mlx);

		if (ft_walls_check(mlx->map, (int)(mlx->player->x - cosf(mlx->player->pov) * 0.5), (int)mlx->player->y))
			mlx->player->x -= cosf(mlx->player->pov) * 0.25;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y + sinf(mlx->player->pov) * 0.5)))
			mlx->player->y += sinf(mlx->player->pov) * 0.25;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
		ft_thread(mlx);
	}

	if (keycode == 1739 || keycode == 114)
	{
		ft_reset_image(mlx);			//RESTART SHOULD RE READ MAP AND ETC
		ft_ray_start(mlx);
		ft_thread(mlx);
	}
	
	if (keycode == 65453 && mlx->player->hp > 5)	//HP
	{
		mlx->player->hp -= 5;
		ft_reset_image(mlx);
		ft_thread(mlx);
	}

	if (keycode == 65451 && mlx->player->hp < 100)
	{
		mlx->player->hp += 5;
		ft_reset_image(mlx);
		ft_thread(mlx);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_mlx *mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->player = (t_player *)malloc(sizeof(t_player));

	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Wolf3D");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	mlx->depth_buff = (double*)malloc(sizeof(double) * W);

	ft_read_map(argv[1], mlx);

	mlx->sprite_order = (int*)malloc(sizeof(int) * mlx->obj_count);
	mlx->sprite_dist = (double*)malloc(sizeof(double) * mlx->obj_count);

	ft_init_textures(mlx);
	ft_init_objects(mlx);
	ft_init_cobjects(mlx);

	ft_read_obj(mlx);

	ft_ray_start(mlx);
	ft_thread(mlx);

	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	// mlx_hook(mlx->win, 4, 1L << 2, mouse_press, mlx);
	// mlx_hook(mlx->win, 5, 1L << 3, mouse_release, mlx);
	// mlx_hook(mlx->win, 6, 1L << 6, mouse_move, mlx);

	mlx_loop(mlx->mlx);
	return (0);
}