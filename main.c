/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:40:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/04/10 23:23:50 by zjeyne-l         ###   ########.fr       */
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

void ft_fill_map(t_mlx *mlx)
{
	mlx->map[0] =  	"122211121100000000000000035W5W5400000";
	mlx->map[1] = 	"100000000100000000004343F4000003F3433";
	mlx->map[2] = 	"2000000001000000000030000000000000004";
	mlx->map[3] = 	"10000000012211121112E000000000000000E";
	mlx->map[4] = 	"2000000001000000000200000000000000003";
	mlx->map[5] = 	"#000000000000000000000000000000000004";
	mlx->map[6] = 	"2000000002000000000100000000000000004";
	mlx->map[7] = 	"10000000011220000111E000000000000000E";
	mlx->map[8] = 	"2000000002001100110040000000000000004";
	mlx->map[9] = 	"1000000001000200200033G3430000034G343";
	mlx->map[10] = "2120120122000100200000000311021100000";
	mlx->map[11] = "0022222200000200100000000010002000000";
	mlx->map[12] = "0000000000000100200000000020002000000";
	mlx->map[13] = "0001111111110200100000000010002000000";
	mlx->map[14] = "0021020201021100200000000020001000000";
	mlx->map[15] = "0010000000001000100000000020002000000";
	mlx->map[16] = "00#0000000000000100000000010001000000";
	mlx->map[17] = "0010000000001000200000000020001000000";
	mlx->map[18] = "0021010101021112100000000010002000000";
	mlx->map[19] = "0001111111110000000000000020002000000";
	mlx->map[20] = "0000000000000000000000000020001000000";
	mlx->map[21] = "0000000000000000000000000010002000000";
	mlx->map[22] = "0000000000000000000001121211011111210";
	mlx->map[23] = "0000000000000000000002000010001000020";
	mlx->map[24] = "000000000000000000000100B000C00000020";
	mlx->map[25] = "0000000000000000000001000010001000020";
	mlx->map[26] = "0000000000000000000002000020002000020";
	mlx->map[27] = "0000000000000000000001121120001111110";
	mlx->map[28] = "0000000000000000000001000010001000010";
	mlx->map[29] = "0000000000000000000002000000C00000020";
	mlx->map[30] = "0000000000000000000001000010001000010";
	mlx->map[31] = "0000000000000000000001221120002112110";
	mlx->map[32] = "0000000000000000000001000000000000010";
	mlx->map[33] = "000000000000000000000200C000C000C0010";
	mlx->map[34] = "0000000000000000000001000000000000010";
	mlx->map[35] = "0000000000000000000001#21#12S12#21#10";
}

void	ft_show_map(t_mlx *mlx)
{
	int i = 0;
	while (i < mlx->row)
	{
		printf("%s\n", mlx->map[i]);
		i++;
	}
}

void	ft_map(t_mlx *mlx)
{
	int i;
	i = 0;
	mlx->map = (char **)malloc(sizeof(char *) * 36);
	while (i < 36)
	{
		mlx->map[i] = (char *)malloc(sizeof(char) * 37);
		i++;
	}
	ft_fill_map(mlx);
}

int		key_press(int keycode, t_mlx *mlx)
{
	//printf("%d\n", keycode);
	(keycode == 1755) ? ft_show_map(mlx) : 1;
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

	if (keycode == 1731 || keycode == 119)	//FORWARD
	{
		ft_reset_image(mlx);

		if ((ft_walls_check(mlx->map, (int)(mlx->player->x + sinf(mlx->player->pov) * 0.4), (int)mlx->player->y)))
			mlx->player->x += sinf(mlx->player->pov) * 0.4;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y + cosf(mlx->player->pov) * 0.4)))
			mlx->player->y += cosf(mlx->player->pov) * 0.4;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
		ft_thread(mlx);
	}

	if (keycode == 1753 || keycode == 115)	//BACK
	{
		ft_reset_image(mlx);

		if ((ft_walls_check(mlx->map, (int)(mlx->player->x - sinf(mlx->player->pov) * 0.4), (int)mlx->player->y)))
			mlx->player->x -= sinf(mlx->player->pov) * 0.4;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y - cosf(mlx->player->pov) * 0.4)))
			mlx->player->y -= cosf(mlx->player->pov) * 0.4;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
		ft_thread(mlx);
	}

	if (keycode == 1751)	//RIGHT
	{
		ft_reset_image(mlx);

		if (ft_walls_check(mlx->map, (int)(mlx->player->x + cosf(mlx->player->pov) * 0.25), (int)mlx->player->y))
			mlx->player->x += cosf(mlx->player->pov) * 0.25;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y - sinf(mlx->player->pov) * 0.25)))
			mlx->player->y -= sinf(mlx->player->pov) * 0.25;
		ft_on_item_check(mlx, (int)mlx->player->x, (int)mlx->player->y);
		ft_thread(mlx);
	}

	if (keycode == 1734)	//LEFT
	{
		ft_reset_image(mlx);

		if (ft_walls_check(mlx->map, (int)(mlx->player->x - cosf(mlx->player->pov) * 0.25), (int)mlx->player->y))
			mlx->player->x -= cosf(mlx->player->pov) * 0.25;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y + sinf(mlx->player->pov) * 0.25)))
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