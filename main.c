/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:40:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/22 16:24:19 by zjeyne-l         ###   ########.fr       */
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
	mlx->map[0] = 	"00000333333400000";
	mlx->map[1] = 	"4343F4000003F3433";
	mlx->map[2] = 	"30000000000000004";
	mlx->map[3] = 	"E000000000000000E";
	mlx->map[4] = 	"10000000000000003";
	mlx->map[5] = 	"10000000000000004";
	mlx->map[6] = 	"10000000000000004";
	mlx->map[7] = 	"E000000000000000E";
	mlx->map[8] = 	"40000000000000004";
	mlx->map[9] = 	"33G3430000034G343";
	mlx->map[10] = 	"00000311021100000";
	mlx->map[11] = 	"00000010002000000";
	mlx->map[12] = 	"00000020002000000";
	mlx->map[13] = 	"00000010002000000";
	mlx->map[14] = 	"00000020001000000";
	mlx->map[15] = 	"00000020002000000";
	mlx->map[16] = 	"00000010001000000";
	mlx->map[17] = 	"00000020001000000";
	mlx->map[18] = 	"00000010002000000";
	mlx->map[19] = 	"00000020002000000";
	mlx->map[20] = "00000020001000000";
	mlx->map[21] = "00000010002000000";
	mlx->map[22] = "01121211011111210";
	mlx->map[23] = "02000010001000020";
	mlx->map[24] = "01000000000000020";
	mlx->map[25] = "01000010001000020";
	mlx->map[26] = "02000020002000020";
	mlx->map[27] = "01121120001111110";
	mlx->map[28] = "01000010001000010";
	mlx->map[29] = "02000000000000020";
	mlx->map[30] = "01000010001000010";
	mlx->map[31] = "01221120002112110";
	mlx->map[32] = "01000000000000010";
	mlx->map[33] = "02000000000000010";
	mlx->map[34] = "01000000000000010";
	mlx->map[35] = "01#21#12S12#21#10";
}

void ft_map(t_mlx *mlx)
{
	int i;
	i = 0;
	mlx->map = (char **)malloc(sizeof(char *) * 36);
	while (i < 36)
	{
		mlx->map[i] = (char *)malloc(sizeof(char) * 17);
		i++;
	}
	ft_fill_map(mlx);
}

int mouse_move(int x, int y, t_mlx *mlx)
{
	if (mlx->slider->lmb_hold == 1)
	{
		if (x >= mlx->slider->x - mlx->slider->radius && x <= mlx->slider->x + mlx->slider->radius && y >= mlx->slider->y - mlx->slider->radius && y <= mlx->slider->y + mlx->slider->radius)
			mlx->slider->is_grabbed = 1;
	}
	if (mlx->slider->is_grabbed == 1)
	{
		if (x >= mlx->slider->xo - mlx->slider->len && x <= mlx->slider->xo)
		{
			ft_reset_image(mlx);
			ft_slider_line(mlx, x);
			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		}
		else
		{
			if (x < mlx->slider->xo - mlx->slider->len)
			{
				ft_reset_image(mlx);
				ft_slider_line(mlx, mlx->slider->xo - mlx->slider->len);
				mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
			}
			if (x > mlx->slider->xo)
			{
				ft_reset_image(mlx);
				ft_slider_line(mlx, mlx->slider->xo);
				mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
			}
		}
		// if (abs(mlx->slider->x - x) > 5)				NOT SURE ABOUT IT
		// {
		// 	if (x >= mlx->slider->xo - mlx->slider->len && x <= mlx->slider->xo)
		// 	{
		// 			ft_reset_image(mlx);
		// 			ft_slider_line(mlx, x);
		// 			mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		// 	}
		// }
	}
	return (0);
}

int mouse_release(int button, int x, int y, t_mlx *mlx)
{
	if (button == 1)
	{
		mlx->slider->lmb_hold = 0;
		mlx->slider->is_grabbed = 0;
	}
	return (0);
}

int mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(button == 1) ? mlx->slider->lmb_hold = 1 : 1;
	if (x >= mlx->slider->xo - mlx->slider->len && x <= mlx->slider->xo && y >= mlx->slider->y - mlx->slider->height && y <= mlx->slider->y + mlx->slider->height)
	{
		ft_reset_image(mlx);
		ft_slider_line(mlx, x);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}
	return (0);
}

int key_press(int keycode, t_mlx *mlx)
{
	//printf("%d\n", keycode);
	(keycode == 65307) ? exit(0) : 1;

	if (keycode == 61)
	{
		ft_reset_image(mlx);
		mlx->player->fov += 0.1;
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 45)
	{
		ft_reset_image(mlx);
		mlx->player->fov -= 0.1;
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 65361)
	{
		ft_reset_image(mlx);
		mlx->player->pov -= 0.075;
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 65363)
	{
		ft_reset_image(mlx);
		mlx->player->pov += 0.075;
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 1731 || keycode == 119)	//FORWARD
	{
		ft_reset_image(mlx);

		// if (mlx->map[(int)mlx->player->y][(int)(mlx->player->x + sinf(mlx->player->pov) * 0.4)] != WALL)
		// 	mlx->player->x += sinf(mlx->player->pov) * 0.4;
		// if (mlx->map[(int)(mlx->player->y + cosf(mlx->player->pov) * 0.4)][(int)mlx->player->x] != WALL)
		// 	mlx->player->y += cosf(mlx->player->pov) * 0.4;

		if ((ft_walls_check(mlx->map, (int)(mlx->player->x + sinf(mlx->player->pov) * 0.4), (int)mlx->player->y)))
			mlx->player->x += sinf(mlx->player->pov) * 0.4;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y + cosf(mlx->player->pov) * 0.4)))
			mlx->player->y += cosf(mlx->player->pov) * 0.4;
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 1753 || keycode == 115)	//BACK
	{
		ft_reset_image(mlx);

		// if (mlx->map[(int)mlx->player->y][(int)(mlx->player->x - sinf(mlx->player->pov) * 0.4)] != WALL)
		// 	mlx->player->x -= sinf(mlx->player->pov) * 0.4;
		// if (mlx->map[(int)(mlx->player->y - cosf(mlx->player->pov) * 0.4)][(int)mlx->player->x] != WALL)
		// 	mlx->player->y -= cosf(mlx->player->pov) * 0.4;

		if ((ft_walls_check(mlx->map, (int)(mlx->player->x - sinf(mlx->player->pov) * 0.4), (int)mlx->player->y)))
			mlx->player->x -= sinf(mlx->player->pov) * 0.4;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y - cosf(mlx->player->pov) * 0.4)))
			mlx->player->y -= cosf(mlx->player->pov) * 0.4;
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 1751)	//RIGHT
	{
		ft_reset_image(mlx);

		// if (mlx->map[(int)mlx->player->y][(int)(mlx->player->x + cosf(mlx->player->pov) * 0.25)] != WALL)
		// 	mlx->player->x += cosf(mlx->player->pov) * 0.25;
		// if (mlx->map[(int)(mlx->player->y - sinf(mlx->player->pov) * 0.25)][(int)mlx->player->x] != WALL)
		// 	mlx->player->y -= sinf(mlx->player->pov) * 0.25;

		if (ft_walls_check(mlx->map, (int)(mlx->player->x + cosf(mlx->player->pov) * 0.25), (int)mlx->player->y))
			mlx->player->x += cosf(mlx->player->pov) * 0.25;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y - sinf(mlx->player->pov) * 0.25)))
			mlx->player->y -= sinf(mlx->player->pov) * 0.25;
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 1734)	//LEFT
	{
		ft_reset_image(mlx);

		// if (mlx->map[(int)mlx->player->y][(int)(mlx->player->x - cosf(mlx->player->pov) * 0.25)] != WALL)
		// 	mlx->player->x -= cosf(mlx->player->pov) * 0.25;
		// if (mlx->map[(int)(mlx->player->y + sinf(mlx->player->pov) * 0.25)][(int)mlx->player->x] != WALL)
		// 	mlx->player->y += sinf(mlx->player->pov) * 0.25;

		if (ft_walls_check(mlx->map, (int)(mlx->player->x - cosf(mlx->player->pov) * 0.25), (int)mlx->player->y))
			mlx->player->x -= cosf(mlx->player->pov) * 0.25;
		if (ft_walls_check(mlx->map, (int)mlx->player->x, (int)(mlx->player->y + sinf(mlx->player->pov) * 0.25)))
			mlx->player->y += sinf(mlx->player->pov) * 0.25;
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	// if (keycode == 45 && mlx->player->fov > 1,05)
	// {
	// 	ft_reset_image(mlx);
	// 	mlx->player->fov -= 0.01;
	// 	printf("fov %f\n", mlx->player->fov * 180 / 3.14);
	// 	ft_ray_cast(mlx);
	// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// }

	// if (keycode == 61 && mlx->player->fov < 2.09)
	// {
	// 	ft_reset_image(mlx);
	// 	mlx->player->fov += 0.01;
	// 	printf("fov %f\n", mlx->player->fov * 180 / 3.14);
	// 	ft_ray_cast(mlx);
	// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// }

	if (keycode == 1739 || keycode == 114)
	{
		ft_reset_image(mlx);
		ft_ray_start(mlx);
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}
	return (0);
}

void ft_start(t_mlx *mlx)
{
	mlx->slider->x = W / 2;
	mlx->slider->y = H / 2;
	mlx->slider->xo = W / 2;
	mlx->slider->len = 40;
	mlx->slider->height = 10;
	mlx->slider->radius = 10;
	mlx->slider->lmb_hold = 0;
	mlx->slider->is_grabbed = 0;
}

int main()
{
	t_mlx *mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->player = (t_player *)malloc(sizeof(t_player));
	mlx->slider = (t_slider *)malloc(sizeof(t_slider));

	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Wolf3D");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	ft_map(mlx);

	ft_read_textures(mlx);

	ft_ray_start(mlx);
	ft_ray_cast(mlx);

	//ft_start(mlx);
	//ft_slider_line(mlx, mlx->slider->xo);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win, 4, 1L << 2, mouse_press, mlx);
	mlx_hook(mlx->win, 5, 1L << 3, mouse_release, mlx);
	mlx_hook(mlx->win, 6, 1L << 6, mouse_move, mlx);

	mlx_loop(mlx->mlx);
	return (0);
}