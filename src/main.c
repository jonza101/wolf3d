/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:40:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/03 13:00:20 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_key_tmp(int keycode, t_mlx *mlx)
{
	if (keycode == MAC_D)
	{
		if (ft_walls_check(mlx->map, (int)(mlx->player->x +
					cosf(mlx->player->pov) * 0.5), (int)mlx->player->y))
			mlx->player->x += cosf(mlx->player->pov) * 0.25;
		if (ft_walls_check(mlx->map, (int)mlx->player->x,
					(int)(mlx->player->y - sinf(mlx->player->pov) * 0.5)))
			mlx->player->y -= sinf(mlx->player->pov) * 0.25;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
	}
	if (keycode == MAC_A)
	{
		if (ft_walls_check(mlx->map, (int)(mlx->player->x -
					cosf(mlx->player->pov) * 0.5), (int)mlx->player->y))
			mlx->player->x -= cosf(mlx->player->pov) * 0.25;
		if (ft_walls_check(mlx->map, (int)mlx->player->x,
					(int)(mlx->player->y + sinf(mlx->player->pov) * 0.5)))
			mlx->player->y += sinf(mlx->player->pov) * 0.25;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
	}
}

void	ft_key_temp(int keycode, t_mlx *mlx)
{
	if (keycode == MAC_W)
	{
		if ((ft_walls_check(mlx->map, (int)(mlx->player->x +
					sinf(mlx->player->pov) * 0.8), (int)mlx->player->y)))
			mlx->player->x += sinf(mlx->player->pov) * 0.35;
		if (ft_walls_check(mlx->map, (int)mlx->player->x,
					(int)(mlx->player->y + cosf(mlx->player->pov) * 0.8)))
			mlx->player->y += cosf(mlx->player->pov) * 0.35;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
	}
	if (keycode == MAC_S)
	{
		if ((ft_walls_check(mlx->map, (int)(mlx->player->x -
					sinf(mlx->player->pov) * 0.8), (int)mlx->player->y)))
			mlx->player->x -= sinf(mlx->player->pov) * 0.35;
		if (ft_walls_check(mlx->map, (int)mlx->player->x,
					(int)(mlx->player->y - cosf(mlx->player->pov) * 0.8)))
			mlx->player->y -= cosf(mlx->player->pov) * 0.35;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
	}
	ft_key_tmp(keycode, mlx);
}

int		ft_key_press(int keycode, t_mlx *mlx)
{
	(keycode == MAC_ESC) ? exit(0) : 1;
	if (keycode == MAC_EQUAL && mlx->player->fov < 2.0944f)
		mlx->player->fov += 0.02;
	if (keycode == MAC_MINUS && mlx->player->fov > 1.06465f)
		mlx->player->fov -= 0.02;
	(keycode == MAC_LEFT) ? mlx->player->pov -= 0.065 : 1;
	(keycode == MAC_RIGHT) ? mlx->player->pov += 0.065 : 1;
	ft_key_temp(keycode, mlx);
	if (keycode == MAC_NUM_MINUS && mlx->player->hp > 5)
		mlx->player->hp -= 5;
	if (keycode == MAC_NUM_PLUS && mlx->player->hp < 100)
		mlx->player->hp += 5;
	if (keycode == MAC_COMMA && mlx->depth > 16)
		mlx->depth--;
	if (keycode == MAC_DOT && mlx->depth < 64)
		mlx->depth++;
	return (0);
}

void	ft_init(t_mlx *mlx)
{
	(!(mlx->depth_buff = (double*)malloc(sizeof(double)
								* W))) ? ft_mem_error() : 1;
	(!(mlx->sprite_order = (int*)malloc(sizeof(int)
					* mlx->obj_count))) ? ft_mem_error() : 1;
	(!(mlx->sprite_dist = (double*)malloc(sizeof(double)
					* mlx->obj_count))) ? ft_mem_error() : 1;
	ft_init_textures(mlx);
	ft_init_objects(mlx);
	ft_init_cobjects(mlx);
	ft_read_obj(mlx);
}

int		main(int argc, char **argv)
{
	t_mlx *mlx;

	(argc != 2) ? ft_usage() : 1;
	(!(mlx = (t_mlx *)malloc(sizeof(t_mlx)))) ? ft_mem_error() : 1;
	(!(mlx->player = (t_player*)malloc(sizeof(t_player))))
										? ft_mem_error() : 1;
	mlx->map_file = ft_strdup(argv[1]);
	ft_read_map(mlx->map_file, mlx);
	mlx->mlx = mlx_init();
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	ft_init(mlx);
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Wolf3D");
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp,
								&mlx->size_line, &mlx->endian);
	ft_ray_start(mlx);
	mlx_hook(mlx->win, 2, 1L << 0, ft_key_press, mlx);
	mlx_loop_hook(mlx->mlx, ft_game_loop, mlx);
	mlx_hook(mlx->win, 17, 1L << 0, ft_close, (void*)1);
	mlx_loop(mlx->mlx);
	return (0);
}
