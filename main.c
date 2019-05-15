/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:40:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/15 18:45:15 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#include <stdio.h>

void	ft_reset_image(t_mlx *mlx)
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
		ft_reset_image(mlx);			//RESTART MUST RE READ MAP

		// ft_read_map(mlx->map_file, mlx);
		// ft_read_obj(mlx);
		
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

	(argc != 2) ? ft_usage() : 1;

	(!(mlx = (t_mlx *)malloc(sizeof(t_mlx)))) ? ft_mem_error() : 1;
	(!(mlx->player = (t_player *)malloc(sizeof(t_player)))) ? ft_mem_error() : 1;
	
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Wolf3D");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	(!(mlx->depth_buff = (double*)malloc(sizeof(double) * W))) ? ft_mem_error() : 1;

	mlx->map_file = ft_strdup(argv[1]);
	ft_read_map(mlx->map_file, mlx);

	printf("asd1\n\n");

	(!(mlx->sprite_order = (int*)malloc(sizeof(int) * mlx->obj_count))) ? ft_mem_error() : 1;
	(!(mlx->sprite_dist = (double*)malloc(sizeof(double) * mlx->obj_count))) ? ft_mem_error() : 1;

	ft_init_textures(mlx);
	// printf("asd\n");
	ft_init_objects(mlx);
	// printf("asd\n");
	ft_init_cobjects(mlx);
	// printf("asd\n");

	ft_read_obj(mlx);

	ft_ray_start(mlx);
	ft_thread(mlx);

	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);

	mlx_loop(mlx->mlx);
	return (0);
}